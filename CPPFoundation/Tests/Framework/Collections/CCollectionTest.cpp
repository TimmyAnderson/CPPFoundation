//----------------------------------------------------------------------------------------------------------------------
#include "CCollectionTest.h"
#include <Framework/Foundation/Collections/CMap.h>
#include <Framework/Foundation/Collections/CMultiMap.h>
#include <Framework/Foundation/Collections/CMultiSet.h>
#include <Framework/Foundation/Collections/CSet.h>
#include <Framework/Foundation/Collections/CTuple.h>
#include <Framework/Foundation/Console/CConsoleHelper.h>
#include <Framework/Foundation/Types/CMethod.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CCollectionTest::CCollectionTest(CLogWriter& LogWriter, const CLogCategory& LogCategoryTest)
		: CTest(LogWriter,LogCategoryTest,"COLLECTION TEST")
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CCollectionTest::~CCollectionTest(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCollectionTest::TestSet1(void)
	{
		try
		{
			CSet<CString>										Set1;

			Set1.Add("12");
			Set1.Add("12");
			Set1.Add("11");
			Set1.Add("11");
			Set1.Add("13");
			Set1.Add("13");

			if (Set1.GetLength()!=3)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CSet<CString>										Set2(Set1);

			if (Set2.GetLength()!=3)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CSet<CString>										Set3(FUNCTION_MOVE(Set1));

			if (Set3.GetLength()!=3)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CSet<CString>										Set4(Set3.DynamicCastReference<IEnumerableConst<CString>>());

			if (Set4.GetLength()!=3)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CSet<CString>										Set5({"12","12","11","11","13","13"});

			if (Set5.GetLength()!=3)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CSet<CString>										Set6;

			Set6=Set4;

			if (Set6.GetLength()!=3)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CSet<CString>										Set7;

			Set7=FUNCTION_MOVE(Set4);

			if (Set7.GetLength()!=3)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CSet<CString>										Set8;

			Set8=CVector<CString>({"12","12","11","11","13","13"});

			if (Set8.GetLength()!=3)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CSet<CString>										Set9;

			Set9=CVector<CString>({"12","12","11","11","13","13"}).DynamicCastReference<IEnumerable<CString>>();

			if (Set9.GetLength()!=3)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CSet<CString>										Set10;

			Set10={"12","12","11","11","13","13"};

			if (Set10.GetLength()!=3)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST SET 1 FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST SET 1 FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCollectionTest::TestSet2(void)
	{
		try
		{
			CSet<CString>										Set;
			const CSet<CString>&								Constset=Set;

			Set.IsEmpty();

			Set.GetEnumeratorConst()->MoveNext();

			CString												Key1("12");
			CString												Key2("11");

			Set.Add(Key1);
			Set.Insert("12");
			Set.Insert(Key2);
			Set.Add("11");
			Set.Add("13");
			Set.Add("13");

			Set.IsEmpty();

			if (Set.GetLength()!=3)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			{
				CSet<CString>::CEnumeratorConstPointer			Enumerator=Set.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					Enumerator->GetCurrentConst();
				}

				Enumerator->MoveNext();

				try
				{
					Enumerator->GetCurrentConst();

					return(false);
				}
				catch(const CException&)
				{
				}
			}

			for(CSet<CString>::CSetIterator Iterator=Set.begin();Iterator!=Set.end();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CSet<CString>::CSetIteratorConst Iterator=Constset.begin();Iterator!=Constset.end();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CSet<CString>::CSetIterator Iterator=Set.Begin();Iterator!=Set.End();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CSet<CString>::CSetIteratorConst Iterator=Constset.Begin();Iterator!=Constset.End();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CSet<CString>::CSetIteratorConst Iterator=Constset.ConstBegin();Iterator!=Constset.ConstEnd();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CSet<CString>::CSetReverseIterator Iterator=Set.ReverseBegin();Iterator!=Set.ReverseEnd();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CSet<CString>::CSetReverseIteratorConst Iterator=Constset.ReverseBegin();Iterator!=Constset.ReverseEnd();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CSet<CString>::CSetReverseIteratorConst Iterator=Constset.ConstReverseBegin();Iterator!=Constset.ConstReverseEnd();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CSet<CString>::CSetIterator Iterator=Set.Begin();!(Iterator==Set.End());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CSet<CString>::CSetIteratorConst Iterator=Constset.Begin();!(Iterator==Constset.End());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CSet<CString>::CSetReverseIterator Iterator=Set.ReverseBegin();!(Iterator==Set.ReverseEnd());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CSet<CString>::CSetReverseIteratorConst Iterator=Constset.ReverseBegin();!(Iterator==Constset.ReverseEnd());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CSet<CString>::CSetReverseIterator Iterator=Set.rbegin();!(Iterator==Set.rend());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CSet<CString>::CSetReverseIteratorConst Iterator=Constset.rbegin();!(Iterator==Constset.rend());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			if (Set.Erase("11")==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tERASE FAILED !\n"));
				return(false);
			}

			if (Set.Erase("ZZZ")==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tERASE FAILED !\n"));
				return(false);
			}

			if (Set.Contains("11")==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tCONTAINS FAILED !\n"));
				return(false);
			}

			if (Set.GetLength()!=2)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CSet<CString>::CSetIteratorConst					LowerBound1=Set.LowerBound("11");

			if (*(LowerBound1)!="12")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			CSet<CString>::CSetIteratorConst					LowerBound2=Constset.LowerBound("11");

			if (*(LowerBound2)!="12")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			CSet<CString>::CSetIteratorConst					UpperBound1=Set.UpperBound("12");

			if (*(UpperBound1)!="13")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			CSet<CString>::CSetIteratorConst					UpperBound2=Constset.UpperBound("12");

			if (*(UpperBound2)!="13")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST SET 2 FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST SET 2 FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCollectionTest::TestMultiSet1(void)
	{
		try
		{
			CMultiSet<CString>									Multiset1;

			Multiset1.Add("12");
			Multiset1.Add("12");
			Multiset1.Add("11");
			Multiset1.Add("11");
			Multiset1.Add("13");
			Multiset1.Add("13");

			if (Multiset1.GetLength()!=6)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMultiSet<CString>									Multiset2(Multiset1);

			if (Multiset2.GetLength()!=6)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMultiSet<CString>									Multiset3(FUNCTION_MOVE(Multiset1));

			if (Multiset3.GetLength()!=6)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMultiSet<CString>									Multiset4(Multiset3.DynamicCastReference<IEnumerableConst<CString>>());

			if (Multiset4.GetLength()!=6)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMultiSet<CString>									Multiset5({"12","12","11","11","13","13"});

			if (Multiset5.GetLength()!=6)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMultiSet<CString>									Multiset6;

			Multiset6=Multiset4;

			if (Multiset6.GetLength()!=6)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMultiSet<CString>									Multiset7;

			Multiset7=FUNCTION_MOVE(Multiset4);

			if (Multiset7.GetLength()!=6)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMultiSet<CString>									Multiset8;

			Multiset8=CVector<CString>({"12","12","11","11","13","13"});

			if (Multiset8.GetLength()!=6)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMultiSet<CString>									Multiset9;

			Multiset9=CVector<CString>({"12","12","11","11","13","13"}).DynamicCastReference<IEnumerable<CString>>();

			if (Multiset9.GetLength()!=6)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMultiSet<CString>									Multiset10;

			Multiset10={"12","12","11","11","13","13"};

			if (Multiset10.GetLength()!=6)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MULTISET 1 FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MULTISET 1 FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCollectionTest::TestMultiSet2(void)
	{
		try
		{
			CMultiSet<CString>									Multiset;
			const CMultiSet<CString>&							ConstMultiset=Multiset;

			Multiset.IsEmpty();

			Multiset.GetEnumeratorConst()->MoveNext();

			CString												Key1("12");
			CString												Key2("11");

			Multiset.Add(Key1);
			Multiset.Insert("12");
			Multiset.Insert(Key2);
			Multiset.Add("11");
			Multiset.Add("13");
			Multiset.Add("13");

			Multiset.IsEmpty();

			if (Multiset.GetLength()!=6)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			{
				CMultiSet<CString>::CEnumeratorConstPointer		Enumerator=Multiset.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					Enumerator->GetCurrentConst();
				}

				Enumerator->MoveNext();

				try
				{
					Enumerator->GetCurrentConst();

					return(false);
				}
				catch(const CException&)
				{
				}
			}

			for(CMultiSet<CString>::CMultiSetIterator Iterator=Multiset.begin();Iterator!=Multiset.end();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiSet<CString>::CMultiSetIteratorConst Iterator=ConstMultiset.begin();Iterator!=ConstMultiset.end();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiSet<CString>::CMultiSetIterator Iterator=Multiset.Begin();Iterator!=Multiset.End();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiSet<CString>::CMultiSetIteratorConst Iterator=ConstMultiset.Begin();Iterator!=ConstMultiset.End();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiSet<CString>::CMultiSetIteratorConst Iterator=ConstMultiset.ConstBegin();Iterator!=ConstMultiset.ConstEnd();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiSet<CString>::CMultiSetReverseIterator Iterator=Multiset.ReverseBegin();Iterator!=Multiset.ReverseEnd();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiSet<CString>::CMultiSetReverseIteratorConst Iterator=ConstMultiset.ReverseBegin();Iterator!=ConstMultiset.ReverseEnd();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiSet<CString>::CMultiSetReverseIteratorConst Iterator=ConstMultiset.ConstReverseBegin();Iterator!=ConstMultiset.ConstReverseEnd();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiSet<CString>::CMultiSetIterator Iterator=Multiset.Begin();!(Iterator==Multiset.End());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiSet<CString>::CMultiSetIteratorConst Iterator=ConstMultiset.Begin();!(Iterator==ConstMultiset.End());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiSet<CString>::CMultiSetReverseIterator Iterator=Multiset.ReverseBegin();!(Iterator==Multiset.ReverseEnd());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiSet<CString>::CMultiSetReverseIteratorConst Iterator=ConstMultiset.ReverseBegin();!(Iterator==ConstMultiset.ReverseEnd());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiSet<CString>::CMultiSetReverseIterator Iterator=Multiset.rbegin();!(Iterator==Multiset.rend());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiSet<CString>::CMultiSetReverseIteratorConst Iterator=ConstMultiset.rbegin();!(Iterator==ConstMultiset.rend());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			if (Multiset.Erase("11")!=2)
			{
				CConsoleHelper::WriteLine(CString::Format("\tERASE FAILED !\n"));
				return(false);
			}

			if (Multiset.Erase("ZZZ")!=0)
			{
				CConsoleHelper::WriteLine(CString::Format("\tERASE FAILED !\n"));
				return(false);
			}

			if (Multiset.Contains("11")==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tCONTAINS FAILED !\n"));
				return(false);
			}

			if (Multiset.GetLength()!=4)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMultiSet<CString>::CMultiSetIteratorConst			LowerBound1=Multiset.LowerBound("11");

			if (*(LowerBound1)!="12")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			CMultiSet<CString>::CMultiSetIteratorConst			LowerBound2=ConstMultiset.LowerBound("11");

			if (*(LowerBound2)!="12")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			CMultiSet<CString>::CMultiSetIteratorConst			UpperBound1=Multiset.UpperBound("12");

			if (*(UpperBound1)!="13")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			CMultiSet<CString>::CMultiSetIteratorConst			UpperBound2=ConstMultiset.UpperBound("12");

			if (*(UpperBound2)!="13")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			CPair<CMultiSet<CString>::CMultiSetIterator,CMultiSet<CString>::CMultiSetIterator>	Range1=Multiset.Range("12");

			if (*(Range1.GetFirst())!="12")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			Range1.GetFirst()++;

			if (*(Range1.GetFirst())!="12")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			Range1.GetFirst()++;

			if (*(Range1.GetFirst())!="13")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			CPair<CMultiSet<CString>::CMultiSetIterator,CMultiSet<CString>::CMultiSetIterator>	Range2=ConstMultiset.Range("12");

			if (*(Range2.GetFirst())!="12")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			Range2.GetFirst()++;

			if (*(Range2.GetFirst())!="12")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			Range2.GetFirst()++;

			if (*(Range2.GetFirst())!="13")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MULTISET 1 FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MULTISET 1 FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCollectionTest::TestMap1(void)
	{
		try
		{
			CMap<CString,CString>								Map1;

			Map1.AddOrReplace("12","22");
			Map1.AddOrReplace("12","22");
			Map1.AddOrReplace("11","21");
			Map1.AddOrReplace("11","21");
			Map1.AddOrReplace("13","23");
			Map1.AddOrReplace("13","23");

			if (Map1.GetLength()!=3)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMap<CString,CString>								Map2(Map1);

			if (Map2.GetLength()!=3)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMap<CString,CString>								Map3(FUNCTION_MOVE(Map1));

			if (Map3.GetLength()!=3)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMap<CString,CString>								Map4({CPair<CString,CString>("12","22"),CPair<CString,CString>("11","12"),CPair<CString,CString>("31","32")});

			if (Map4.GetLength()!=3)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMap<CString,CString>								Map5;

			Map5=Map4;

			if (Map5.GetLength()!=3)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMap<CString,CString>								Map6;

			Map6=FUNCTION_MOVE(Map4);

			if (Map6.GetLength()!=3)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMap<CString,CString>								Map7;

			Map7.Add("12","22");

			try
			{
				Map7.Add("12","22");

				return(false);
			}
			catch(const CException&)
			{
			}

			CString												Key("15");
			CString												Value("25");

			Map7.Add(Key,Value);

			try
			{
				Map7.Add(Key,Value);

				return(false);
			}
			catch(const CException&)
			{
			}

			Map7.Add("11",CString("21"));

			try
			{
				Map7.Add("11",CString("21"));

				return(false);
			}
			catch(const CException&)
			{
			}

			CPair<CString,CString>								Pair("13","23");

			Map7.Add(Pair);

			try
			{
				Map7.Add(Pair);

				return(false);
			}
			catch(const CException&)
			{
			}

			Map7.Add(CPair<CString,CString>("14","24"));

			try
			{
				Map7.Add(CPair<CString,CString>("14","24"));

				return(false);
			}
			catch(const CException&)
			{
			}

			if (Map7.GetLength()!=5)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MAP 1 FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MAP 1 FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCollectionTest::TestMap2(void)
	{
		try
		{
			CMap<CString,CString>								Map;
			const CMap<CString,CString>&						ConstMap=Map;
			CString												Key="12";
			CString												Value="22";

			Map.AddOrReplace(Key,Value);
			Map.AddOrReplace(Key,Value);
			Map.AddOrReplace("11","21");
			Map.AddOrReplace("11","21");
			Map.AddOrReplace("13","23");
			Map.AddOrReplace(CPair<CString,CString>("13","23"));

			for(CPair<const CString,CString>& Pair : Map)
			{
				Pair.GetFirst();
			}

			for(const CPair<const CString,CString>& Pair : Map)
			{
				Pair.GetFirst();
			}

			for(const CPair<const CString,CString>& Pair : ConstMap)
			{
				Pair.GetFirst();
			}

			for(CMap<CString,CString>::CMapIterator Iterator=Map.Begin();Iterator!=Map.End();Iterator++)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMap<CString,CString>::CMapIteratorConst Iterator=ConstMap.Begin();Iterator!=ConstMap.End();Iterator++)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMap<CString,CString>::CMapIteratorConst Iterator=ConstMap.ConstBegin();Iterator!=ConstMap.ConstEnd();Iterator++)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMap<CString,CString>::CMapReverseIterator Iterator=Map.ReverseBegin();Iterator!=Map.ReverseEnd();Iterator++)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMap<CString,CString>::CMapReverseIteratorConst Iterator=ConstMap.ConstReverseBegin();Iterator!=ConstMap.ConstReverseEnd();Iterator++)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMap<CString,CString>::CMapReverseIteratorConst Iterator=ConstMap.ReverseBegin();Iterator!=ConstMap.ReverseEnd();Iterator++)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMap<CString,CString>::CMapIterator Iterator=Map.Begin();!(Iterator==Map.End());++Iterator)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMap<CString,CString>::CMapIteratorConst Iterator=ConstMap.Begin();!(Iterator==ConstMap.End());++Iterator)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMap<CString,CString>::CMapReverseIterator Iterator=Map.ReverseBegin();!(Iterator==Map.ReverseEnd());++Iterator)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMap<CString,CString>::CMapReverseIteratorConst Iterator=ConstMap.ReverseBegin();!(Iterator==ConstMap.ReverseEnd());++Iterator)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMap<CString,CString>::CMapReverseIterator Iterator=Map.rbegin();!(Iterator==Map.rend());++Iterator)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMap<CString,CString>::CMapReverseIteratorConst Iterator=ConstMap.rbegin();!(Iterator==ConstMap.rend());++Iterator)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			{
				CMap<CString,CString>::CMapIterator				Iterator=Map.End();

				Iterator--;

				if ((*Iterator).GetFirst()!="13")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="12")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="11")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}
			}

			{
				CMap<CString,CString>::CMapIteratorConst		Iterator=ConstMap.End();

				Iterator--;

				if ((*Iterator).GetFirst()!="13")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="12")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="11")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}
			}

			{
				CMap<CString,CString>::CMapReverseIterator		Iterator=Map.rend();

				Iterator--;

				if ((*Iterator).GetFirst()!="11")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="12")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="13")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}
			}

			{
				CMap<CString,CString>::CMapReverseIteratorConst	Iterator=ConstMap.rend();

				Iterator--;

				if ((*Iterator).GetFirst()!="11")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="12")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="13")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}
			}

			{
				CMap<CString,CString>::CMapIterator	Iterator=Map.begin();
				const CMap<CString,CString>::CMapIterator& ConstIterator=Iterator;

				ConstIterator->GetFirst();
				(*ConstIterator).GetFirst();
			}

			{
				CMap<CString,CString>::CMapReverseIterator		Iterator=Map.rbegin();
				const CMap<CString,CString>::CMapReverseIterator&	ConstIterator=Iterator;

				ConstIterator->GetFirst();
				(*ConstIterator).GetFirst();
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MAP 2 FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MAP 2 FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCollectionTest::TestMap3(void)
	{
		try
		{
			CMap<CString,CString>								Map;
			const CMap<CString,CString>&						ConstMap=Map;

			Map.AddOrReplace("12","22");
			Map.AddOrReplace("12","22");
			Map.AddOrReplace("11","21");
			Map.AddOrReplace("11","21");
			Map.AddOrReplace("13","23");
			Map.AddOrReplace("13","23");

			for(CMap<CString,CString>::CMapValueIterator Iterator=Map.BeginValue();Iterator!=Map.EndValue();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMap<CString,CString>::CMapValueIteratorConst Iterator=ConstMap.BeginValue();Iterator!=ConstMap.EndValue();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMap<CString,CString>::CMapValueReverseIterator Iterator=Map.ReverseBeginValue();Iterator!=Map.ReverseEndValue();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMap<CString,CString>::CMapValueReverseIteratorConst Iterator=ConstMap.ReverseBeginValue();Iterator!=ConstMap.ReverseEndValue();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMap<CString,CString>::CMapValueIterator Iterator=Map.BeginValue();!(Iterator==Map.EndValue());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMap<CString,CString>::CMapValueIteratorConst Iterator=ConstMap.BeginValue();!(Iterator==ConstMap.EndValue());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMap<CString,CString>::CMapValueReverseIterator Iterator=Map.ReverseBeginValue();!(Iterator==Map.ReverseEndValue());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMap<CString,CString>::CMapValueReverseIteratorConst Iterator=ConstMap.ReverseBeginValue();!(Iterator==ConstMap.ReverseEndValue());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			{
				CMap<CString,CString>::CMapValueIterator		Iterator=Map.EndValue();

				Iterator--;

				if ((*Iterator)!="23")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(Iterator--))!="23")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*Iterator)!="22")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="21")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}
			}

			{
				CMap<CString,CString>::CMapValueIteratorConst	Iterator=ConstMap.EndValue();

				Iterator--;

				if ((*Iterator)!="23")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(Iterator--))!="23")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*Iterator)!="22")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="21")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}
			}

			{
				CMap<CString,CString>::CMapValueReverseIterator	Iterator=Map.ReverseEndValue();

				Iterator--;

				if ((*Iterator)!="21")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(Iterator--))!="21")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*Iterator)!="22")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="23")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}
			}

			{
				CMap<CString,CString>::CMapValueReverseIteratorConst	Iterator=ConstMap.ReverseEndValue();

				Iterator--;

				if ((*Iterator)!="21")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(Iterator--))!="21")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*Iterator)!="22")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="23")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}
			}

			{
				CMap<CString,CString>::CMapValueIterator		Iterator=Map.BeginValue();
				const CMap<CString,CString>::CMapValueIterator&	ConstIterator=Iterator;

				ConstIterator->ToString();
				(*ConstIterator).ToString();
			}

			{
				CMap<CString,CString>::CMapValueReverseIterator	Iterator=Map.ReverseBeginValue();
				const CMap<CString,CString>::CMapValueReverseIterator& ConstIterator=Iterator;

				ConstIterator->ToString();
				(*ConstIterator).ToString();
			}

			{
				CString											Key("11");

				Map[Key].ToString();
			}

			{
				CString											Key("11");

				ConstMap[Key].ToString();
			}

			Map["11"].ToString();
			ConstMap["11"].ToString();

			try
			{
				CString											Key("ZZZ");

				Map[Key].ToString();

				return(false);
			}
			catch(const CException&)
			{
			}

			try
			{
				CString											Key("ZZZ");

				ConstMap[Key].ToString();

				return(false);
			}
			catch(const CException&)
			{
			}

			try
			{
				Map["ZZZ"].ToString();

				return(false);
			}
			catch(const CException&)
			{
			}

			try
			{
				ConstMap["ZZZ"].ToString();

				return(false);
			}
			catch(const CException&)
			{
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MAP 3 FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MAP 3 FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCollectionTest::TestMap4(void)
	{
		try
		{
			CMap<CString,CString>								Map;
			const CMap<CString,CString>&						ConstMap=Map;

			{
				CMap<CString,CString>::CEnumeratorPointer		Enumerator=Map.GetEnumerator();

				while(Enumerator->MoveNext()==true)
				{
					Enumerator->GetCurrent();
					Enumerator->GetCurrentConst();
				}
			}

			{
				CMap<CString,CString>::CEnumeratorConstPointer	Enumerator=ConstMap.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					Enumerator->GetCurrentConst();
				}
			}

			Map.AddOrReplace("12","22");
			Map.AddOrReplace("12","22");
			Map.AddOrReplace("11","21");
			Map.AddOrReplace("11","21");
			Map.AddOrReplace("13","23");
			Map.AddOrReplace("13","23");

			{
				CMap<CString,CString>::CEnumeratorPointer		Enumerator=Map.GetEnumerator();

				while(Enumerator->MoveNext()==true)
				{
					Enumerator->GetCurrent();
					Enumerator->GetCurrentConst();
				}

				Enumerator->MoveNext();

				try
				{
					Enumerator->GetCurrent();

					return(false);
				}
				catch(const CException&)
				{
				}

				try
				{
					Enumerator->GetCurrentConst();

					return(false);
				}
				catch(const CException&)
				{
				}
			}

			{
				CMap<CString,CString>::CEnumeratorConstPointer	Enumerator=ConstMap.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					Enumerator->GetCurrentConst();
				}

				Enumerator->MoveNext();

				try
				{
					Enumerator->GetCurrentConst();

					return(false);
				}
				catch(const CException&)
				{
				}
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MAP 4 FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MAP 4 FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCollectionTest::TestMap5(void)
	{
		try
		{
			CMap<CString,CString>								Map;
			const CMap<CString,CString>&						ConstMap=Map;

			Map.AddOrReplace("XXX","XXX");
			Map.AddOrReplace("YYY","YYY");

			Map.Erase(Map.Begin());
			Map.Erase(Map.ConstBegin());

			CString												Key="13";
			CString												Value="113";
			CPair<CString,CString>								Pair("11","111");

			Map.AddOrReplace(Key,Value);
			Map.AddOrReplace(CPair<CString,CString>("11","111"));

			Map.Insert("12","112");
			Map.Insert(Key,Value);
			Map.Insert(Pair);
			Map.Insert(CPair<CString,CString>("14","114"));

			Map.Insert(CPair<CString,CString>("15","115"));
			Map.Insert(CPair<CString,CString>("15","215"));
			Map.Insert(CPair<CString,CString>("15","315"));

			CMap<CString,CString>::CMapIterator					LowerBound1=Map.LowerBound("14");

			if (LowerBound1->GetSecond()!="114")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			CMap<CString,CString>::CMapIteratorConst			LowerBound2=ConstMap.LowerBound("14");

			if (LowerBound2->GetSecond()!="114")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			CMap<CString,CString>::CMapIterator					UpperBound1=Map.UpperBound("14");

			if (UpperBound1->GetSecond()!="115")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			CMap<CString,CString>::CMapIteratorConst			UpperBound2=ConstMap.UpperBound("14");

			if (UpperBound2->GetSecond()!="115")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			Map.GetKeys();
			Map.GetValues();

			if (Map.Erase(Key)==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tERASE FAILED !\n"));
				return(false);
			}

			if (Map.Erase(Key)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tERASE FAILED !\n"));
				return(false);
			}

			Map.Find("12");
			ConstMap.Find("12");

			if (ConstMap.Contains("13")==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tCONTAINS FAILED !\n"));
				return(false);
			}

			if (ConstMap.GetValueOrDefault("12")!="112")
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET VALUE or DEFAULT FAILED !\n"));
				return(false);
			}

			if (ConstMap.Contains("12")==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tCONTAINS FAILED !\n"));
				return(false);
			}

			Map.IsEmpty();

			Map.Clear();

			Map.IsEmpty();

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MAP 5 FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MAP 5 FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCollectionTest::TestMultiMap1(void)
	{
		try
		{
			CMultiMap<CString,CString>							Multimap1;

			Multimap1.Add("12","22");
			Multimap1.Add("12","22");
			Multimap1.Add("11","21");
			Multimap1.Add("11","21");
			Multimap1.Add("13","23");
			Multimap1.Add("13","23");

			if (Multimap1.GetLength()!=6)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMultiMap<CString,CString>							Multimap2(Multimap1);

			if (Multimap2.GetLength()!=6)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMultiMap<CString,CString>							Multimap3(FUNCTION_MOVE(Multimap1));

			if (Multimap3.GetLength()!=6)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMultiMap<CString,CString>							Multimap4({CPair<CString,CString>("12","22"),CPair<CString,CString>("12","22"),CPair<CString,CString>("11","12"),CPair<CString,CString>("11","12"),CPair<CString,CString>("31","32"),CPair<CString,CString>("31","32")});

			if (Multimap4.GetLength()!=6)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMultiMap<CString,CString>							Multimap5;

			Multimap5=Multimap4;

			if (Multimap5.GetLength()!=6)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			CMultiMap<CString,CString>							Multimap6;

			Multimap6=FUNCTION_MOVE(Multimap4);

			if (Multimap6.GetLength()!=6)
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID LENGTH !\n"));
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MULTIMAP 1 FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MULTIMAP 1 FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCollectionTest::TestMultiMap2(void)
	{
		try
		{
			CMultiMap<CString,CString>							Multimap;
			const CMultiMap<CString,CString>&					ConstMultimap=Multimap;

			Multimap.Add("12","22");
			Multimap.Add("12","22");
			Multimap.Add("11","21");
			Multimap.Add("11","21");
			Multimap.Add("13","23");
			Multimap.Add("13","23");

			for(CPair<const CString,CString>& Pair : Multimap)
			{
				Pair.GetFirst();
			}

			for(const CPair<const CString,CString>& Pair : Multimap)
			{
				Pair.GetFirst();
			}

			for(const CPair<const CString,CString>& Pair : ConstMultimap)
			{
				Pair.GetFirst();
			}

			for(CMultiMap<CString,CString>::CMultiMapIterator Iterator=Multimap.Begin();Iterator!=Multimap.End();Iterator++)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMultiMap<CString,CString>::CMultiMapIteratorConst Iterator=ConstMultimap.Begin();Iterator!=ConstMultimap.End();Iterator++)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMultiMap<CString,CString>::CMultiMapIteratorConst Iterator=Multimap.ConstBegin();Iterator!=Multimap.ConstEnd();Iterator++)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMultiMap<CString,CString>::CMultiMapReverseIterator Iterator=Multimap.ReverseBegin();Iterator!=Multimap.ReverseEnd();Iterator++)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMultiMap<CString,CString>::CMultiMapReverseIteratorConst Iterator=ConstMultimap.ReverseBegin();Iterator!=ConstMultimap.ReverseEnd();Iterator++)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMultiMap<CString,CString>::CMultiMapReverseIteratorConst Iterator=ConstMultimap.ConstReverseBegin();Iterator!=ConstMultimap.ConstReverseEnd();Iterator++)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMultiMap<CString,CString>::CMultiMapIterator Iterator=Multimap.Begin();!(Iterator==Multimap.End());++Iterator)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMultiMap<CString,CString>::CMultiMapIteratorConst Iterator=ConstMultimap.Begin();!(Iterator==ConstMultimap.End());++Iterator)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMultiMap<CString,CString>::CMultiMapReverseIterator Iterator=Multimap.ReverseBegin();!(Iterator==Multimap.ReverseEnd());++Iterator)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMultiMap<CString,CString>::CMultiMapReverseIteratorConst Iterator=ConstMultimap.ReverseBegin();!(Iterator==ConstMultimap.ReverseEnd());++Iterator)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMultiMap<CString,CString>::CMultiMapReverseIterator Iterator=Multimap.rbegin();!(Iterator==Multimap.rend());++Iterator)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			for(CMultiMap<CString,CString>::CMultiMapReverseIteratorConst Iterator=ConstMultimap.rbegin();!(Iterator==ConstMultimap.rend());++Iterator)
			{
				Iterator->GetFirst();
				(*Iterator).GetFirst();
			}

			{
				CMultiMap<CString,CString>::CMultiMapIterator	Iterator=Multimap.End();

				Iterator--;

				if ((*Iterator).GetFirst()!="13")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="13")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="12")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="12")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="11")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="11")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}
			}

			{
				CMultiMap<CString,CString>::CMultiMapIteratorConst	Iterator=ConstMultimap.End();

				Iterator--;

				if ((*Iterator).GetFirst()!="13")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="13")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="12")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="12")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="11")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="11")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}
			}

			{
				CMultiMap<CString,CString>::CMultiMapReverseIterator	Iterator=Multimap.rend();

				Iterator--;

				if ((*Iterator).GetFirst()!="11")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="11")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="12")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="12")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="13")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="13")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}
			}

			{
				CMultiMap<CString,CString>::CMultiMapReverseIteratorConst	Iterator=ConstMultimap.rend();

				Iterator--;

				if ((*Iterator).GetFirst()!="11")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="11")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="12")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="12")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="13")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator)).GetFirst()!="13")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}
			}

			{
				CMultiMap<CString,CString>::CMultiMapIterator	Iterator=Multimap.begin();
				const CMultiMap<CString,CString>::CMultiMapIterator& ConstIterator=Iterator;

				ConstIterator->GetFirst();
				(*ConstIterator).GetFirst();
			}

			{
				CMultiMap<CString,CString>::CMultiMapReverseIterator	Iterator=Multimap.rbegin();
				const CMultiMap<CString,CString>::CMultiMapReverseIterator& ConstIterator=Iterator;

				ConstIterator->GetFirst();
				(*ConstIterator).GetFirst();
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MULTIMAP 2 FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MULTIMAP 2 FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCollectionTest::TestMultiMap3(void)
	{
		try
		{
			CMultiMap<CString,CString>							Multimap;
			const CMultiMap<CString,CString>&					ConstMultimap=Multimap;

			Multimap.Add("12","22");
			Multimap.Add("12","22");
			Multimap.Add("11","21");
			Multimap.Add("11","21");
			Multimap.Add("13","23");
			Multimap.Add("13","23");

			for(CMultiMap<CString,CString>::CMultiMapValueIterator Iterator=Multimap.BeginValue();Iterator!=Multimap.EndValue();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiMap<CString,CString>::CMultiMapValueIteratorConst Iterator=ConstMultimap.BeginValue();Iterator!=ConstMultimap.EndValue();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiMap<CString,CString>::CMultiMapValueReverseIterator Iterator=Multimap.ReverseBeginValue();Iterator!=Multimap.ReverseEndValue();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiMap<CString,CString>::CMultiMapValueReverseIteratorConst Iterator=ConstMultimap.ReverseBeginValue();Iterator!=ConstMultimap.ReverseEndValue();Iterator++)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiMap<CString,CString>::CMultiMapValueIterator Iterator=Multimap.BeginValue();!(Iterator==Multimap.EndValue());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiMap<CString,CString>::CMultiMapValueIteratorConst Iterator=ConstMultimap.BeginValue();!(Iterator==ConstMultimap.EndValue());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiMap<CString,CString>::CMultiMapValueReverseIterator Iterator=Multimap.ReverseBeginValue();!(Iterator==Multimap.ReverseEndValue());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			for(CMultiMap<CString,CString>::CMultiMapValueReverseIteratorConst Iterator=ConstMultimap.ReverseBeginValue();!(Iterator==ConstMultimap.ReverseEndValue());++Iterator)
			{
				Iterator->ToString();
				(*Iterator).ToString();
			}

			{
				CMultiMap<CString,CString>::CMultiMapValueIterator	Iterator=Multimap.EndValue();

				Iterator--;

				if ((*Iterator)!="23")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="23")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(Iterator--))!="23")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*Iterator)!="22")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="22")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="21")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="21")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}
			}

			{
				CMultiMap<CString,CString>::CMultiMapValueIteratorConst	Iterator=ConstMultimap.EndValue();

				Iterator--;

				if ((*Iterator)!="23")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="23")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(Iterator--))!="23")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*Iterator)!="22")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="22")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="21")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="21")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}
			}

			{
				CMultiMap<CString,CString>::CMultiMapValueReverseIterator	Iterator=Multimap.ReverseEndValue();

				Iterator--;

				if ((*Iterator)!="21")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="21")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(Iterator--))!="21")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*Iterator)!="22")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="22")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="23")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="23")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}
			}

			{
				CMultiMap<CString,CString>::CMultiMapValueReverseIteratorConst	Iterator=ConstMultimap.ReverseEndValue();

				Iterator--;

				if ((*Iterator)!="21")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="21")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(Iterator--))!="21")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*Iterator)!="22")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="22")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="23")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}

				if ((*(--Iterator))!="23")
				{
					CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
					return(false);
				}
			}

			{
				CMultiMap<CString,CString>::CMultiMapValueIterator	Iterator=Multimap.BeginValue();
				const CMultiMap<CString,CString>::CMultiMapValueIterator& ConstIterator=Iterator;

				ConstIterator->ToString();
				(*ConstIterator).ToString();
			}

			{
				CMultiMap<CString,CString>::CMultiMapValueReverseIterator	Iterator=Multimap.ReverseBeginValue();
				const CMultiMap<CString,CString>::CMultiMapValueReverseIterator& ConstIterator=Iterator;

				ConstIterator->ToString();
				(*ConstIterator).ToString();
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MULTIMAP 3 FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MULTIMAP 3 FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCollectionTest::TestMultiMap4(void)
	{
		try
		{
			CMultiMap<CString,CString>							Multimap;
			const CMultiMap<CString,CString>&					ConstMultimap=Multimap;

			{
				CMultiMap<CString,CString>::CEnumeratorPointer	Enumerator=Multimap.GetEnumerator();

				while(Enumerator->MoveNext()==true)
				{
					Enumerator->GetCurrent();
					Enumerator->GetCurrentConst();
				}
			}

			{
				CMultiMap<CString,CString>::CEnumeratorConstPointer	Enumerator=ConstMultimap.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					Enumerator->GetCurrentConst();
				}
			}

			Multimap.Add("12","22");
			Multimap.Add("12","22");
			Multimap.Add("11","21");
			Multimap.Add("11","21");
			Multimap.Add("13","23");
			Multimap.Add("13","23");

			{
				CMultiMap<CString,CString>::CEnumeratorPointer	Enumerator=Multimap.GetEnumerator();

				while(Enumerator->MoveNext()==true)
				{
					Enumerator->GetCurrent();
					Enumerator->GetCurrentConst();
				}

				Enumerator->MoveNext();

				try
				{
					Enumerator->GetCurrent();

					return(false);
				}
				catch(const CException&)
				{
				}

				try
				{
					Enumerator->GetCurrentConst();

					return(false);
				}
				catch(const CException&)
				{
				}
			}

			{
				CMultiMap<CString,CString>::CEnumeratorConstPointer	Enumerator=ConstMultimap.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					Enumerator->GetCurrentConst();
				}

				Enumerator->MoveNext();

				try
				{
					Enumerator->GetCurrentConst();

					return(false);
				}
				catch(const CException&)
				{
				}
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MULTIMAP 4 FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MULTIMAP 4 FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCollectionTest::TestMultiMap5(void)
	{
		try
		{
			CMultiMap<CString,CString>							Multimap;
			const CMultiMap<CString,CString>&					ConstMultimap=Multimap;

			Multimap.Add("XXX","XXX");
			Multimap.Add("YYY","YYY");

			Multimap.Erase(Multimap.Begin());
			Multimap.Erase(Multimap.ConstBegin());

			CString												Key="13";
			CString												Value="113";
			CPair<CString,CString>								Pair("11","111");

			Multimap.Add(Key,Value);
			Multimap.Add(CPair<CString,CString>("11","111"));

			Multimap.Insert("12","112");
			Multimap.Insert(Key,Value);
			Multimap.Insert(Pair);
			Multimap.Insert(CPair<CString,CString>("14","114"));

			Multimap.Insert(CPair<CString,CString>("15","115"));
			Multimap.Insert(CPair<CString,CString>("15","215"));
			Multimap.Insert(CPair<CString,CString>("15","315"));

			CMultiMap<CString,CString>::CMultiMapIterator		LowerBound1=Multimap.LowerBound("14");

			if (LowerBound1->GetSecond()!="114")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			CMultiMap<CString,CString>::CMultiMapIteratorConst	LowerBound2=ConstMultimap.LowerBound("14");

			if (LowerBound2->GetSecond()!="114")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			CMultiMap<CString,CString>::CMultiMapIterator		UpperBound1=Multimap.UpperBound("14");

			if (UpperBound1->GetSecond()!="115")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			CMultiMap<CString,CString>::CMultiMapIteratorConst	UpperBound2=ConstMultimap.UpperBound("14");

			if (UpperBound2->GetSecond()!="115")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			CPair<CMultiMap<CString,CString>::CMultiMapIterator,CMultiMap<CString,CString>::CMultiMapIterator>	Range1=Multimap.Range("15");

			if (Range1.GetFirst()->GetSecond()!="115")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			Range1.GetFirst()++;

			if (Range1.GetFirst()->GetSecond()!="215")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			Range1.GetFirst()++;

			if (Range1.GetFirst()->GetSecond()!="315")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			CPair<CMultiMap<CString,CString>::CMultiMapIteratorConst,CMultiMap<CString,CString>::CMultiMapIteratorConst>	Range2=ConstMultimap.Range("15");

			if (Range2.GetFirst()->GetSecond()!="115")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			Range2.GetFirst()++;

			if (Range2.GetFirst()->GetSecond()!="215")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			Range2.GetFirst()++;

			if (Range2.GetFirst()->GetSecond()!="315")
			{
				CConsoleHelper::WriteLine(CString::Format("\tINVALID VALUE !\n"));
				return(false);
			}

			Multimap.GetKeys();
			Multimap.GetValues();

			if (Multimap.Count(Key)!=2)
			{
				CConsoleHelper::WriteLine(CString::Format("\tCOUNT FAILED !\n"));
				return(false);
			}

			if (Multimap.Erase(Key)!=2)
			{
				CConsoleHelper::WriteLine(CString::Format("\tERASE FAILED !\n"));
				return(false);
			}

			Multimap.Find("12");
			ConstMultimap.Find("12");

			if (ConstMultimap.Contains("13")==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tCONTAINS FAILED !\n"));
				return(false);
			}

			if (ConstMultimap.Contains("12")==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tCONTAINS FAILED !\n"));
				return(false);
			}

			Multimap.IsEmpty();

			Multimap.Clear();

			Multimap.IsEmpty();

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MULTIMAP 5 FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MULTIMAP 5 FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCollectionTest::TestTuple1(void)
	{
		try
		{
			CTuple<CString,CString,int>							Tuple1("AAA","BBB",100);

			if (Tuple1.GetItem<0>()!="AAA")
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			if (Tuple1.GetItem<1>()!="BBB")
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			if (Tuple1.GetItem<2>()!=100)
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			Tuple1.GetItem<0>()="XXX";
			Tuple1.GetItem<1>()="YYY";
			Tuple1.GetItem<2>()=200;

			if (Tuple1.GetItem<0>()!="XXX")
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			if (Tuple1.GetItem<1>()!="YYY")
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			if (Tuple1.GetItem<2>()!=200)
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			if (Tuple1.ToString()!="[XXX] [YYY] [200]")
			{
				CConsoleHelper::WriteLine(CString::Format("\tTO STRING FAILED !\n"));
				return(false);
			}

			CString												Parameter("MMM");

			Tuple1.SetItem<0>(Parameter);
			Tuple1.SetItem<1>("NNN");
			Tuple1.SetItem<2>(300);

			if (Tuple1.GetItem<0>()!="MMM")
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			if (Tuple1.GetItem<1>()!="NNN")
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			if (Tuple1.GetItem<2>()!=300)
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			CTuple<CString,CString,int>							Tuple2(Tuple1);

			if (Tuple2.GetItem<0>()!="MMM")
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			if (Tuple2.GetItem<1>()!="NNN")
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			if (Tuple2.GetItem<2>()!=300)
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			CTuple<CString,CString,int>							Tuple3(FUNCTION_MOVE(Tuple2));

			if (Tuple3.GetItem<0>()!="MMM")
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			if (Tuple3.GetItem<1>()!="NNN")
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			if (Tuple3.GetItem<2>()!=300)
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			CTuple<CString,CString,int>							Tuple4;

			Tuple4=Tuple3;

			if (Tuple4.GetItem<0>()!="MMM")
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			if (Tuple4.GetItem<1>()!="NNN")
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			if (Tuple4.GetItem<2>()!=300)
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			CTuple<CString,CString,int>							Tuple5;

			Tuple5=FUNCTION_MOVE(Tuple3);

			if (Tuple5.GetItem<0>()!="MMM")
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			if (Tuple5.GetItem<1>()!="NNN")
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			if (Tuple5.GetItem<2>()!=300)
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			CString												StringParam("AAA");

			CTuple<CString,CString,int>							Tuple6(StringParam,"BBB1",100);
			CTuple<CString,CString,int>							Tuple7("AAA","BBB2",100);

			if ((Tuple4==Tuple5)==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tOPERATOR== FAILED !\n"));
				return(false);
			}

			if ((Tuple4!=Tuple5)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tOPERATOR== FAILED !\n"));
				return(false);
			}

			if ((Tuple4==Tuple6)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tOPERATOR== FAILED !\n"));
				return(false);
			}

			if ((Tuple4!=Tuple6)==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tOPERATOR!= FAILED !\n"));
				return(false);
			}

			if ((Tuple6<Tuple7)==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tOPERATOR< FAILED !\n"));
				return(false);
			}

			if ((Tuple6>Tuple7)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tOPERATOR> FAILED !\n"));
				return(false);
			}

			if ((Tuple6<=Tuple7)==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tOPERATOR<= FAILED !\n"));
				return(false);
			}

			if ((Tuple6>=Tuple7)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tOPERATOR>= FAILED !\n"));
				return(false);
			}

			if ((Tuple7<Tuple6)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tOPERATOR< FAILED !\n"));
				return(false);
			}

			if ((Tuple7>Tuple6)==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tOPERATOR> FAILED !\n"));
				return(false);
			}

			if ((Tuple7<=Tuple6)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tOPERATOR<= FAILED !\n"));
				return(false);
			}

			if ((Tuple7>=Tuple6)==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tOPERATOR>= FAILED !\n"));
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST TUPLE 1 FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST TUPLE 1 FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCollectionTest::TestTuple2(void)
	{
		try
		{
			const CTuple<CString,CString,int>					Tuple("AAA","BBB",100);

			if (Tuple.GetItem<0>()!="AAA")
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			if (Tuple.GetItem<1>()!="BBB")
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			if (Tuple.GetItem<2>()!=100)
			{
				CConsoleHelper::WriteLine(CString::Format("\tGET ITEM FAILED !\n"));
				return(false);
			}

			if (Tuple.ToString()!="[AAA] [BBB] [100]")
			{
				CConsoleHelper::WriteLine(CString::Format("\tTO STRING FAILED !\n"));
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST TUPLE 2 FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST TUPLE 2 FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCollectionTest::ExecuteTest(void)
	{
		CVector<CTestMethod<CCollectionTest>>					Tests;

		Tests.Add(CTestMethod<CCollectionTest>(this,&CCollectionTest::TestSet1));
		Tests.Add(CTestMethod<CCollectionTest>(this,&CCollectionTest::TestSet2));
		Tests.Add(CTestMethod<CCollectionTest>(this,&CCollectionTest::TestMultiSet1));
		Tests.Add(CTestMethod<CCollectionTest>(this,&CCollectionTest::TestMultiSet2));
		Tests.Add(CTestMethod<CCollectionTest>(this,&CCollectionTest::TestMap1));
		Tests.Add(CTestMethod<CCollectionTest>(this,&CCollectionTest::TestMap2));
		Tests.Add(CTestMethod<CCollectionTest>(this,&CCollectionTest::TestMap3));
		Tests.Add(CTestMethod<CCollectionTest>(this,&CCollectionTest::TestMap4));
		Tests.Add(CTestMethod<CCollectionTest>(this,&CCollectionTest::TestMap5));
		Tests.Add(CTestMethod<CCollectionTest>(this,&CCollectionTest::TestMultiMap1));
		Tests.Add(CTestMethod<CCollectionTest>(this,&CCollectionTest::TestMultiMap2));
		Tests.Add(CTestMethod<CCollectionTest>(this,&CCollectionTest::TestMultiMap3));
		Tests.Add(CTestMethod<CCollectionTest>(this,&CCollectionTest::TestMultiMap4));
		Tests.Add(CTestMethod<CCollectionTest>(this,&CCollectionTest::TestMultiMap5));
		Tests.Add(CTestMethod<CCollectionTest>(this,&CCollectionTest::TestTuple1));
		Tests.Add(CTestMethod<CCollectionTest>(this,&CCollectionTest::TestTuple2));

		bool													AllTestPassed=true;
		Size													TestNumber=0;
		
		for(CTestMethod<CCollectionTest>& Method : Tests)
		{
			if (Method()==true)
			{
				CString											Output;

				Output+=GetSeparator(true);
				Output+="\tSUBTEST [";
				Output+=CString(++TestNumber);
				Output+="] PASSED SUCCESSFULLY !\n";
				Output+=GetSeparator(true);

				CConsoleHelper::WriteLine(Output,EConsoleColor::E_LIGHT_GREEN,EConsoleColor::E_DEFAULT,false);
			}
			else
			{
				CString											Output;

				Output+=GetSeparator(true);
				Output+="\tSUBTEST [";
				Output+=CString(++TestNumber);
				Output+="] FAILED !\n";
				Output+=GetSeparator(true);

				AllTestPassed=false;

				CConsoleHelper::WriteLine(Output,EConsoleColor::E_LIGHT_RED,EConsoleColor::E_DEFAULT,false);
			}
		}

		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));

		if (AllTestPassed==true)
		{
			CConsoleHelper::WriteLine("ALL TESTS PASSED SUCCESSFULLY !",EConsoleColor::E_LIGHT_GREEN,EConsoleColor::E_DEFAULT,false);
		}
		else
		{
			CConsoleHelper::WriteLine("SOME TESTS FAILED !",EConsoleColor::E_LIGHT_RED,EConsoleColor::E_DEFAULT,false);
		}

		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));

		return(AllTestPassed);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------