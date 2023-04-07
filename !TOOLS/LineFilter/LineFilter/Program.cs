using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Loader;
using System.Text;
using System.Configuration;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.Emit;
//----------------------------------------------------------------------------------------------------------------------
namespace LineFilter
{
//----------------------------------------------------------------------------------------------------------------------
    public class Program
    {
//----------------------------------------------------------------------------------------------------------------------
		private static Assembly CreateAssembly(string CodeToCompile)
		{
			SyntaxTree											Tree=CSharpSyntaxTree.ParseText(CodeToCompile);
			string												AssemblyName=Path.GetRandomFileName();
			MetadataReference[]									References=new MetadataReference[]
			{
				MetadataReference.CreateFromFile(typeof(object).GetTypeInfo().Assembly.Location),
				MetadataReference.CreateFromFile(typeof(Console).GetTypeInfo().Assembly.Location)
			};

			List<SyntaxTree>									SyntaxTrees=new List<SyntaxTree>();

			SyntaxTrees.Add(Tree);

			CSharpCompilation									Compilation=CSharpCompilation.Create(AssemblyName,SyntaxTrees,References,new CSharpCompilationOptions(OutputKind.DynamicallyLinkedLibrary));

			using(MemoryStream Stream=new MemoryStream())
			{
				EmitResult										CompilationResult=Compilation.Emit(Stream);

				if (CompilationResult.Success==true)
				{
					Stream.Seek(0,SeekOrigin.Begin);

					Assembly									GeneratedAssembly=AssemblyLoadContext.Default.LoadFromStream(Stream);

					return(GeneratedAssembly);
				}
				else
				{
					StringBuilder								SB=new StringBuilder();

					foreach(Diagnostic Error in CompilationResult.Diagnostics)
					{
						SB.AppendLine($"ERROR [{Error}] !");
					}

					throw(new InvalidOperationException(SB.ToString()));
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private static string CreateSourceCode(List<string> Values)
		{
			StringBuilder										Code=new StringBuilder();

			Code.AppendLine("using System;");
			Code.AppendLine();
			Code.AppendLine("namespace Generated");
			Code.AppendLine("{");
			Code.AppendLine("\tpublic class CComparer");
			Code.AppendLine("\t{");

			for(int Index=0;Index<Values.Count;Index++)
			{
				string											Value=Values[Index];

				Code.AppendLine($"\t\tpublic static bool Condition{(Index+1)}(string Line)");
				Code.AppendLine("\t\t{");

				Code.AppendLine($"\t\t\treturn({Value});");

				Code.AppendLine("\t\t}");
			}

			Code.AppendLine("\t\tpublic static bool AcceptLine(string Line)");
			Code.AppendLine("\t\t{");

			Code.Append("\t\t\treturn(");

			if (Values.Count>0)
			{
				for(int Index=0;Index<Values.Count;Index++)
				{
					if (Index>0)
					{
						Code.Append(" || ");
					}

					Code.Append($"Condition{(Index+1)}(Line)");
				}
			}
			else
			{
				Code.Append("false");
			}

			Code.AppendLine(");");

			Code.AppendLine("\t\t}");

			Code.AppendLine("\t}");
			Code.Append("}");

			string												CodeString=Code.ToString();

			return (CodeString);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static string ReadFile(string Path)
		{
			string												FileContent;

			using(FileStream FS=File.OpenRead(Path))
			{
				using(StreamReader SR=new StreamReader(FS))
				{
					FileContent=SR.ReadToEnd();
				}
			}

			return(FileContent);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        public static void Main(string[] args)
        {
			try
			{
				int												NumberOfLineSeparators=int.Parse(ConfigurationManager.AppSettings["NumberOfLineSeparators"]);
				string											Path=ConfigurationManager.AppSettings["Path"];
				string											FileContent=ReadFile(Path);

				List<string>									Values=new List<string>();

				for(int Index=0;Index<ConfigurationManager.AppSettings.Keys.Count;Index++)
				{
					string										Key=ConfigurationManager.AppSettings.Keys[Index];
				
					if (Key.ToUpper().StartsWith("CONDITION")==true)
					{
						Values.Add(ConfigurationManager.AppSettings[Key]);
					}
				}

				string											CodeToCompile=CreateSourceCode(Values);
				string											PrintCode=ConfigurationManager.AppSettings["PrintCode"].ToUpper();

				if (PrintCode=="TRUE")
				{
					Console.WriteLine(CodeToCompile);
				}

				Assembly										GeneratedAssembly=CreateAssembly(CodeToCompile);

				Type											GeneratedType=GeneratedAssembly.GetType("Generated.CComparer");
				MethodInfo										GeneratedMethod=GeneratedType.GetMember("AcceptLine").First() as MethodInfo;

				using(StringReader SR=new StringReader(FileContent))
				{
					bool										AddLineSeparator=false;
					string										Line;

					while((Line=SR.ReadLine())!=null)
					{
						bool									Result=(bool) GeneratedMethod.Invoke(null,new object[]{Line});

						if (Result==true)
						{
							if (AddLineSeparator==false)
							{
								AddLineSeparator=true;
							}
							else
							{
								for(int Index=0;Index<NumberOfLineSeparators;Index++)
								{
									Console.WriteLine();
								}
							}

							Console.WriteLine(Line);
						}
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E}] !");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------