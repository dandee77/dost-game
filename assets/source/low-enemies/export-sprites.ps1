param([switch]$IdleOnly)
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
# Mechanical export of AI-authored frames; no procedural creature/animation drawing.
Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Collections.Generic;
public static class LowEnemyExport {
    public static Rectangle Bounds(Bitmap image, int left, int top, int width, int height) {
        int minX=width, minY=height, maxX=-1, maxY=-1;
        for(int y=0;y<height;y++) for(int x=0;x<width;x++) {
            if(image.GetPixel(left+x,top+y).A<128) continue;
            minX=Math.Min(minX,x); minY=Math.Min(minY,y);
            maxX=Math.Max(maxX,x); maxY=Math.Max(maxY,y);
        }
        return maxX<0 ? Rectangle.Empty : new Rectangle(minX,minY,maxX-minX+1,maxY-minY+1);
    }
    public static void Export(string source, string output, int columns, int rows, int frames, string intact) {
        using(var image=new Bitmap(source))
        using(var result=new Bitmap(frames*64,64,PixelFormat.Format32bppArgb)) {
            int cellW=image.Width/columns, cellH=image.Height/rows;
            Rectangle anchor=Bounds(image,0,0,cellW,cellH);
            var rowAnchors=new Rectangle[rows];
            if(anchor.IsEmpty) throw new Exception("Empty first frame: "+source);
            double dstX=32,dstY=32,scale;
            bool death=!String.IsNullOrEmpty(intact);
            if(death) {
                using(var idle=new Bitmap(intact)) {
                    var target=Bounds(idle,0,0,64,64);
                    scale=Math.Max(target.Width,target.Height)/(double)Math.Max(anchor.Width,anchor.Height);
                    dstX=target.X+target.Width/2.0; dstY=target.Y+target.Height/2.0;
                    for(int y=0;y<64;y++) for(int x=0;x<64;x++) result.SetPixel(x,y,idle.GetPixel(x,y));
                }
            } else {
                // Preserve limb motion within each row; correct the generator's row placement.
                // A single scale for the entire loop prevents per-frame size changes.
                int extent=0;
                for(int row=0;row<rows;row++) {
                    for(int column=0;column<columns&&row*columns+column<frames;column++) {
                        var next=Bounds(image,column*cellW,row*cellH,cellW,cellH);
                        if(next.IsEmpty) throw new Exception("Missing idle frame");
                        rowAnchors[row]=column==0 ? next : Rectangle.Union(rowAnchors[row],next);
                    }
                    extent=Math.Max(extent,Math.Max(rowAnchors[row].Width,rowAnchors[row].Height));
                }
                scale=32.0/extent;
            }
            double srcX=anchor.X+anchor.Width/2.0, srcY=anchor.Y+anchor.Height/2.0;
            for(int frame=death?1:0;frame<(death?frames-1:frames);frame++) {
                if(!death) {
                    var row=rowAnchors[frame/columns];
                    srcX=row.X+row.Width/2.0; srcY=row.Y+row.Height/2.0;
                }
                for(int y=0;y<64;y++) for(int x=0;x<64;x++) {
                    int localX=(int)Math.Floor(srcX+(x+0.5-dstX)/scale);
                    int localY=(int)Math.Floor(srcY+(y+0.5-dstY)/scale);
                    if(localX<0||localX>=cellW||localY<0||localY>=cellH) continue;
                    var c=image.GetPixel((frame%columns)*cellW+localX,(frame/columns)*cellH+localY);
                    if(c.A>=128) result.SetPixel(frame*64+x,y,Color.FromArgb(255,c.R,c.G,c.B));
                }
            }
            result.Save(output,ImageFormat.Png);
        }
    }
    public static string Validate(string path, int frames, bool death) {
        using(var image=new Bitmap(path)) {
            if(image.Width!=frames*64||image.Height!=64) throw new Exception("Wrong dimensions: "+path);
            var counts=new List<int>(); var hashes=new HashSet<int>();
            for(int frame=0;frame<frames;frame++) {
                int count=0,hash=17;
                for(int y=0;y<64;y++) for(int x=0;x<64;x++) {
                    var c=image.GetPixel(frame*64+x,y);
                    if(c.A!=0&&c.A!=255) throw new Exception("Soft alpha: "+path);
                    if(c.A>0) {
                        count++;
                        if(x==0||y==0||x==63||y==63) throw new Exception("Clipped frame: "+path);
                    }
                    unchecked { hash=hash*31+c.ToArgb(); }
                }
                if(count==0&&!(death&&frame==frames-1)) throw new Exception("Empty animation frame: "+path);
                if(death&&frame==frames-1&&count>0) throw new Exception("Nonempty death endpoint: "+path);
                counts.Add(count); hashes.Add(hash);
            }
            if(hashes.Count<frames/2) throw new Exception("Insufficient frame variation: "+path);
            return System.IO.Path.GetFileName(path)+": "+image.Width+"x64; unique frames="+hashes.Count+"; opaque pixels="+String.Join(",",counts);
        }
    }
    public static void Preview(string root, string output) {
        using(var result=new Bitmap(1280,6*128,PixelFormat.Format32bppArgb)) {
            using(var g=Graphics.FromImage(result)) g.Clear(Color.FromArgb(18,14,30));
            for(int variant=1;variant<=3;variant++) for(int death=0;death<=1;death++) {
                string path=System.IO.Path.Combine(root,"low_level_enemy"+variant+(death==1?"_destruct":"")+".png");
                using(var sheet=new Bitmap(path)) {
                    for(int y=0;y<64;y++) for(int x=0;x<sheet.Width;x++) {
                        var c=sheet.GetPixel(x,y); if(c.A==0) continue;
                        for(int sy=0;sy<2;sy++) for(int sx=0;sx<2;sx++)
                            result.SetPixel(x*2+sx,((variant-1)*2+death)*128+y*2+sy,c);
                    }
                }
            }
            result.Save(output,ImageFormat.Png);
        }
    }
}
'@
$textureRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '../../textures'))
$names = @('can-biter','battery-crawler','monitor-parasite')
$idleCounts = @(10,5,5)
$deathCounts = @(8,8,7)
$report = @()
for ($index=0; $index -lt 3; $index++) {
    $number = $index+1
    $idle = Join-Path $textureRoot "low_level_enemy$number.png"
    [LowEnemyExport]::Export((Join-Path $PSScriptRoot "$($names[$index])-idle-generated.png"), $idle, 5, ($idleCounts[$index]/5), $idleCounts[$index], $null)
    $report += [LowEnemyExport]::Validate($idle, $idleCounts[$index], $false)
    if (-not $IdleOnly) {
        $death = Join-Path $textureRoot "low_level_enemy${number}_destruct.png"
        [LowEnemyExport]::Export((Join-Path $PSScriptRoot "$($names[$index])-death-generated.png"), $death, 4, 2, $deathCounts[$index], $idle)
        $report += [LowEnemyExport]::Validate($death, $deathCounts[$index], $true)
    }
}
$report | Set-Content (Join-Path $PSScriptRoot 'validation.txt')
$report
if (-not $IdleOnly) { [LowEnemyExport]::Preview($textureRoot,(Join-Path $PSScriptRoot 'sprites-preview.png')) }
