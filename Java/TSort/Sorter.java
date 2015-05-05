package TSort;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

// (c) Sean Reardon 2014

public class Sorter
{
	String pathToOutput = "sample";

	//default constructor if you wanted to add the pathToOutput later
	public Sorter()
	{

	}
	//main constructor
	public Sorter(String pathToOutput)
	{
		this.pathToOutput = pathToOutput;
	}
	//creates two directories if they don't exist, places files in corresponding directories
	void sortTiffAndWave() throws IOException
	{
		//start with the directory containing all of the files to be sorted
		File dir = new File(pathToOutput);
		File[] directoryListing = dir.listFiles();
		
		if (directoryListing != null)
		{
				//make the TIFF and WAVEFORM directories, if they already exist nothing happpens
				File TIFF = new File(pathToOutput + "/TIFF");
				TIFF.mkdir();	
			
				File WAVEFORM = new File(pathToOutput + "/WAVEFORM");
				WAVEFORM.mkdir();	

				//loop thru each child and sort it
				for(File child : directoryListing)
				{
					//every child thats not the TIFF or WAVEFORM directory
					if(!child.getName().equals("TIFF") && !child.getName().equals("WAVEFORM") )
					{
						//creates the files new path
						String reName = pathToOutput+"/"+getDirectoryFromExtention(child)+ "/"+child.getName();

						//renames the file
						child.renameTo(new File(reName));
					}
					
				}
		}

	}

	//parses the file name to get the extension destination
	String getDirectoryFromExtention(File child)
	{
		String name = child.getName();
		String destination = "";
		boolean extention = false;
		//loop thru the name, find the . save all of the charaters after the period
		//saves the file type in destination
		for(int i = 0; i < name.length(); i++)
		{
			if(extention == true)
			{
				destination = destination + name.charAt(i);
			}
			if(name.charAt(i)=='.')
			{
				extention = true;
			}
		}
		//choose the correct destination based off of extension
		switch (destination)
		{
			case "tiff": 
				destination = "TIFF";
				break;
			case "tif":
				destination = "TIFF";
				break;
			case "wav":
				destination = "WAVEFORM";
				break;
			default:
				break;

		}
		return destination.toUpperCase();
	}
	//tiff files need separate directories withing the tiff directory
	void sortTiffFiles()
	{
		ArrayList<String> toBeDirectory = new ArrayList<String>(0);
		//for each file, if folder does not exist, create it, then move folders
		File dir = new File(pathToOutput+"/TIFF");
		File[] directoryListing = dir.listFiles();
		if (directoryListing != null)
		{
			for(File child : directoryListing)
				{
					createDirectoryListForTiffs(child ,toBeDirectory);
				}
				//create new directories
			for(String s : toBeDirectory)
					{
						new File(dir.getAbsolutePath() + "/" + s).mkdir();
					}
			for(File child : directoryListing)
			{
				//add proper files to proper directory
				if(child.isFile())
				{
					String reName = dir.getAbsolutePath()+"/"+getDestinationDirectoryName(child) + "/"+child.getName();
					child.renameTo(new File(reName));

				}
			}
		}
		
	}
	//check each member of the list against the child, add it to list if it doesn't exist on the list
	void createDirectoryListForTiffs(File child, ArrayList<String> toBeDirectory)
	{
		String tiffDirectory = getDestinationDirectoryName(child);

			boolean isAlreadyOnList = false;
			for(String s : toBeDirectory)
			{
				if(s.equals(tiffDirectory) || s.equals(""))
				{
					isAlreadyOnList = true;
				}
			}		
				if(!isAlreadyOnList)
				{
					toBeDirectory.add(tiffDirectory);
				}
			
	}
	//make the name of the directory based on the numbers of the tiff file
	String getDestinationDirectoryName(File file)
	{

		if(file.isDirectory())
		{
			return "";
		}
		String tiffDirectory ="";
		String getNameFromFile = file.getName();
		//build the directory name, it needs to be the name of the phoneme and the first number
		//if the file is called, err101.tiff we need to have err1 as the directory name
		buildDirectory:
			for(int i = 0; i < (getNameFromFile.length()-1); i++)
			{
				
				char indexChar = getNameFromFile.charAt(i);
				//if its a number
				if(indexChar >= '0' && indexChar <= '9')
				{
					char nextIndexChar = getNameFromFile.charAt(i+1);
					//terminiate the loop if there are two numbers in a row. add the first number
					if(nextIndexChar >= '0' && nextIndexChar <= '9')
					{		
						tiffDirectory = tiffDirectory + indexChar;
						break buildDirectory;
						//shouldn't make this statement, numbers arnt part of phoneme names
						//but just in case they make a weird one lets cover it
					} else {
						tiffDirectory = tiffDirectory + indexChar;
					}
					//if a '.' is found, a mistake has been made
				}else if(indexChar == '.' )
				{
					//the default case, non number, non ., add it to the list
				} else 
				{
					tiffDirectory = tiffDirectory + indexChar;
				}
			}
			return tiffDirectory;
	}

}