using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Configuration;
using System.IO;
//----------------------------------------------------------------------------------------------------------------------
namespace GetCPPDirectories
{
//----------------------------------------------------------------------------------------------------------------------
	class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				string											LinePrefixTabs=ConfigurationManager.AppSettings["LinePrefixTabs"];
				uint											NumberOfTabs;

				if (uint.TryParse(LinePrefixTabs,out NumberOfTabs)==false)
				{
					Console.WriteLine("INVALID VALUE for PARAMETER [LinePrefixTabs] ! NUMERIC VALUE is EXPECTED !");
					return;
				}

				string											Tabs="".PadRight((int) NumberOfTabs,'\t');
				string											LinePrefix=ConfigurationManager.AppSettings["LinePrefix"];
				string											LinePostfix=ConfigurationManager.AppSettings["LinePostfix"];
				string											LineSeparator=ConfigurationManager.AppSettings["LineSeparator"];
				string											LineSeparatorValue;

				if (LineSeparator.ToUpper()=="WINDOWS")
				{
					LineSeparatorValue="\r\n";
				}
				else if (LineSeparator.ToUpper()=="LINUX")
				{
					LineSeparatorValue="\r";
				}
				else
				{
					Console.WriteLine("INVALID VALUE for PARAMETER [LineSeparator] ! Valid VALUES are [WINDOWS] and [LINUX] !");
					return;
				}

				string											RootPath=ConfigurationManager.AppSettings["Path"];
				string											FullRootPath=Path.GetFullPath(RootPath);
				string[]										FileNames=Directory.GetFiles(FullRootPath,"*.cpp",SearchOption.AllDirectories);
				HashSet<string>									Paths=new HashSet<string>();

				if (FullRootPath.EndsWith("\\")==true)
				{
					FullRootPath=FullRootPath.Substring(0,FullRootPath.Length-1);
				}

				foreach(string FileName in FileNames)
				{
					string										FullPath=Path.GetDirectoryName(FileName);
					string										RelativePath=FullPath.Replace(FullRootPath,"");

					if (RelativePath.StartsWith("\\")==true)
                    {
						RelativePath=RelativePath.Substring(1);
					}

					if (RelativePath!="")
					{
						RelativePath+="\\";
					}

					RelativePath=RelativePath.Replace('\\','/');

					Paths.Add(RelativePath);
				}
				
				foreach(string Path in Paths)
				{
					Console.Write(string.Format("{0}{1}{2}{3}{4}",Tabs,LinePrefix,Path,LinePostfix,LineSeparatorValue));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] !",E.Message));
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------