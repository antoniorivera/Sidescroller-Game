package mapreader;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

public class MapReader
{
	public static void main(String[] args)
	{
		int pixel;
		String mapString = "";
		BufferedImage map = null;
		try
		{
			map = ImageIO.read(new File("REPLACE WITH PATH TO IMAGE FILE"));
		} catch(IOException e)
		{
			System.out.println("Error");
		}
		
		for(int row = 0; row < map.getHeight(); row++)
		{
			for(int col = 0; col < map.getWidth(); col++)
			{								//note: 0x00ffffff == ~0xff000000
				pixel = map.getRGB(col,row) & 0x00ffffff;	//extracts just the rgb values. the first two digits from getRGB are alpha channel value (FF means no transparency).
				if(pixel == 0x000000) //black
					mapString += '#';
				else if(pixel == 0xffffff) //white
					mapString += '.';
				else if(pixel == 0xff0000) //red
					mapString += 'r';
				else if(pixel == 0x00ff00) //green
					mapString += 'g';
				else if(pixel == 0x0000ff) //blue
					mapString += 'b';
				else
					System.out.println(Integer.toHexString(pixel));
			}
		}
		
		System.out.println(mapString);
		System.out.println("Width: " + map.getWidth() + "\nHeight: " + map.getHeight());
	}
}
