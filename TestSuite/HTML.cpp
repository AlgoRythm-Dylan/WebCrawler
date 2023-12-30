#include "pch.h"
#include "CppUnitTest.h"

#include <string>
#include <fstream>

#include <HTMLDocument.h>
#include <HTMLNode.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;
using std::ifstream;

namespace TestSuite
{
	TEST_CLASS(TestHTML)
	{
	public:
		TEST_METHOD(TextNodeOnly)
		{
			ifstream file("..\\..\\HTMLFiles\\text-node-only.html");
			Assert::IsTrue(file.is_open());
			HTMLDocument doc;
			doc.parse(file);
			Assert::AreEqual((size_t)1, doc.children.size());
			Assert::AreEqual(string("this is text DIRECTLY on the document\nand it is multiline!"), doc.children[0]->text_content);
		}
		TEST_METHOD(PositiveSelfClosingTag)
		{
			HTMLNode element;
			element.tag_name = "meta";
			Assert::IsTrue(element.is_void_element());
		}
		TEST_METHOD(NegativeSelfClosingTag)
		{
			HTMLNode element;
			element.tag_name = "p";
			Assert::IsFalse(element.is_void_element());
		}
	};
}