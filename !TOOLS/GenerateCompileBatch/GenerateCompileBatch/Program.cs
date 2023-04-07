using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Configuration;
using System.IO;
//----------------------------------------------------------------------------------------------------------------------
namespace GenerateCompileBatch
{
//----------------------------------------------------------------------------------------------------------------------
	class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				string											CompilePrefix=ConfigurationManager.AppSettings["CompilePrefix"];
				string											CompilePostfix=ConfigurationManager.AppSettings["CompilePostfix"];
				string											RootPath=ConfigurationManager.AppSettings["Path"];
				string											BatchFullName=ConfigurationManager.AppSettings["BatchFullName"];
				string											FullRootPath=Path.GetFullPath(RootPath);
				string[]										FileNames=Directory.GetFiles(FullRootPath,"*.cpp",SearchOption.AllDirectories);
				StringBuilder									SB=new StringBuilder();

				foreach(string FileName in FileNames)
				{
					string										RelativePath=FileName.Replace(FullRootPath,"");

					if (RelativePath.StartsWith("\\")==true)
                    {
						RelativePath=RelativePath.Substring(1);
					}

					SB.Append(' ');
					SB.Append(RelativePath);

					Console.WriteLine(string.Format("PATH [{0}] !",RelativePath));
				}
				
				SB.Replace('\\','/');
				SB.Insert(0,CompilePrefix);

				if (CompilePostfix!="")
				{
					SB.Append(" ");
					SB.Append(CompilePostfix);
				}

				string											Content=SB.ToString();

				using(FileStream FS=new FileStream(BatchFullName,FileMode.Create,FileAccess.Write))
				{
					using(StreamWriter SW=new StreamWriter(FS))
					{
						SW.Write(Content);
					}
				}

				Console.WriteLine(string.Format("FILE [{0}] SUCCESSFULLY WRITTEN !",BatchFullName));
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