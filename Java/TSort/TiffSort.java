
package TSort;

import java.io.IOException;


class TiffSort
{
	

	public static void main(String args[])
	{	
		
		Sorter sorter;
		if(args.length > 0)
		{
			sorter = new Sorter(args[0]);
		}else {

			sorter = new Sorter();	
		}
		try 
		{
			sorter.sortTiffAndWave();
			sorter.sortTiffFiles();
		} catch (IOException e)
		{
			System.out.println("When running sortTiffAndWave: \n\t" + e);
		}
		
	}

}