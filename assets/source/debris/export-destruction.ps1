param([string[]]$Names = @('pipe','wing','canister','dish','coil','tank','thruster','beam','hull'))
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
# Mechanical export only: AI-authored 4x2 cells -> native 96px horizontal frames.
Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Collections.Generic;
public static class DestructionExport {
    public static void FitSingle(string source, string output, int bodySize) {
        using(var image=new Bitmap(source)) using(var result=new Bitmap(96,96,PixelFormat.Format32bppArgb)) {
            var b=Bounds(image,0,0,image.Width,image.Height);
            double scale=bodySize/(double)Math.Max(b.Width,b.Height);
            int width=(int)Math.Round(b.Width*scale),height=(int)Math.Round(b.Height*scale);
            for(int y=0;y<height;y++) for(int x=0;x<width;x++) {
                var c=image.GetPixel(b.X+(int)((x+0.5)*b.Width/width),b.Y+(int)((y+0.5)*b.Height/height));
                if(c.A>=128) result.SetPixel((96-width)/2+x,(96-height)/2+y,Color.FromArgb(255,c.R,c.G,c.B));
            }
            result.Save(output,ImageFormat.Png);
        }
    }
    public static Rectangle Bounds(Bitmap image, int left, int top, int width, int height) {
        int minX = left + width, minY = top + height, maxX = -1, maxY = -1;
        for(int y=top;y<top+height;y++) for(int x=left;x<left+width;x++) {
            if(image.GetPixel(x,y).A < 128) continue;
            minX=Math.Min(minX,x); minY=Math.Min(minY,y); maxX=Math.Max(maxX,x); maxY=Math.Max(maxY,y);
        }
        return maxX < 0 ? Rectangle.Empty : new Rectangle(minX,minY,maxX-minX+1,maxY-minY+1);
    }
    public static void Export(string source, string intact, string output) {
        using(var image = new Bitmap(source)) using(var original = new Bitmap(intact))
        using(var result = new Bitmap(768,96,PixelFormat.Format32bppArgb)) {
            double cellW=image.Width/4.0, cellH=image.Height/2.0;
            var bounds=Bounds(image,0,0,(int)cellW,(int)cellH);
            var target=Bounds(original,0,0,96,96);
            double scale=Math.Max(target.Width,target.Height)/(double)Math.Max(bounds.Width,bounds.Height);
            double srcCx=bounds.X+bounds.Width/2.0, srcCy=bounds.Y+bounds.Height/2.0;
            double dstCx=target.X+target.Width/2.0, dstCy=target.Y+target.Height/2.0;
            for(int frame=0;frame<7;frame++) for(int y=0;y<96;y++) for(int x=0;x<96;x++) {
                if(frame==0) { result.SetPixel(x,y,original.GetPixel(x,y)); continue; }
                double localX=srcCx+(x+0.5-dstCx)/scale, localY=srcCy+(y+0.5-dstCy)/scale;
                if(localX<0 || localX>=cellW || localY<0 || localY>=cellH) continue;
                int sx=(int)Math.Floor((frame%4)*cellW+localX), sy=(int)Math.Floor((frame/4)*cellH+localY);
                var c=image.GetPixel(sx,sy);
                if(c.A>=128) result.SetPixel(frame*96+x,y,Color.FromArgb(255,c.R,c.G,c.B));
            }
            result.Save(output,ImageFormat.Png);
        }
    }
    public static double[][] Centers(string path) {
        var result=new List<double[]>();
        using(var image=new Bitmap(path)) {
            var seen=new bool[96*96];
            for(int y=0;y<96;y++) for(int x=0;x<96;x++) {
                int start=y*96+x;
                if(seen[start] || image.GetPixel(576+x,y).A==0) continue;
                var queue=new Queue<int>();queue.Enqueue(start);seen[start]=true;
                double sumX=0,sumY=0;int count=0;
                while(queue.Count>0) {
                    int p=queue.Dequeue(),px=p%96,py=p/96;
                    sumX+=px+0.5;sumY+=py+0.5;count++;
                    for(int dy=-1;dy<=1;dy++) for(int dx=-1;dx<=1;dx++) {
                        int nx=px+dx,ny=py+dy;
                        if(nx<0||nx>=96||ny<0||ny>=96) continue;
                        int key=ny*96+nx;
                        if(!seen[key]&&image.GetPixel(576+nx,ny).A>0) {seen[key]=true;queue.Enqueue(key);}
                    }
                }
                result.Add(new double[]{sumX/count,sumY/count,count});
            }
        }
        return result.ToArray();
    }
}
'@
$textureRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '../../textures/debris'))
foreach ($name in $Names) {
    $source = Join-Path $PSScriptRoot "destruction/$name.png"
    $output = Join-Path $textureRoot "${name}_destruct.png"
    [DestructionExport]::Export($source,(Join-Path $textureRoot "$name.png"),$output)
    $centers = [DestructionExport]::Centers($output)
    @($centers | ForEach-Object { [pscustomobject]@{ x = $_[0]; y = $_[1]; pixels = $_[2] } }) |
        ConvertTo-Json -Depth 5 | Set-Content (Join-Path $PSScriptRoot "destruction/${name}-centers.json")
    Write-Output "$name : $($centers.Length) final flecks"
}
