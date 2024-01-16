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
		TEST_METHOD(TextNodeOnly)
		{
			ifstream file("..\\..\\HTMLFiles\\text-node-only.html");
			Assert::IsTrue(file.is_open());
			HTMLDocument doc;
			doc.parse(file);
			Assert::AreEqual((size_t)1, doc.root->children.size());
			Assert::AreEqual(string("this is text DIRECTLY on the document\nand it is multiline!"), doc.root->children[0]->text_content);
		}
		TEST_METHOD(SimpleDocument)
		{
			ifstream file("..\\..\\HTMLFiles\\simple.html");
			Assert::IsTrue(file.is_open());
			HTMLDocument doc;
			doc.parse(file);
			Assert::AreEqual(string("!DOCTYPE"), doc.root->children[0]->tag_name);
			Assert::AreEqual(string("html"), doc.root->children[1]->tag_name);
			Assert::AreEqual(string("head"), doc.root->children[1]->children[0]->tag_name);
			Assert::AreEqual(string("title"), doc.root->children[1]->children[0]->children[0]->tag_name);
			
			auto bodyTag = doc.root->children[1]->children[1];
			auto h1Tag = bodyTag->children[0];
			auto pTag = bodyTag->children[1];
			
			Assert::AreEqual(string("body"), bodyTag->tag_name);
			Assert::AreEqual(string("h1"), h1Tag->tag_name);
			Assert::AreEqual(string("p"), pTag->tag_name);

			Assert::AreEqual(string("This is a heading!"), h1Tag->children[0]->text_content);
			Assert::AreEqual(string("This is a paragraph!"), pTag->children[0]->text_content);
		}
		TEST_METHOD(HTMLAttributes)
		{
			ifstream file("..\\..\\HTMLFiles\\attributes.html");
			Assert::IsTrue(file.is_open());
			HTMLDocument doc;
			doc.parse(file);
			/*
			
			In place of an HTML query, this hard-coded test case should do

			<!DOCTYPE>
			<html>[1]
				<head>[0]
					<title>[0]
			
			*/
			auto htmlTag = doc.root->children[1];
			auto titleTag = htmlTag->children[0]->children[0];
			auto bodyTag = htmlTag->children[1];
			auto h1Tag = bodyTag->children[0];
			auto pTag = bodyTag->children[1];

			// (First assertion is not a unit test, but to make sure
			// the unit test runs correctly - make sure it's the right tag)
			Assert::AreEqual(string("html"), htmlTag->tag_name);
			Assert::AreEqual((size_t)3, htmlTag->attributes.size());
			Assert::IsTrue(htmlTag->attributes.contains("itemscope"));
			Assert::IsTrue(htmlTag->attributes.contains("itemtype"));
			Assert::IsTrue(htmlTag->attributes.contains("lang"));
			Assert::AreEqual(string(""), htmlTag->attributes["itemscope"]);
			Assert::AreEqual(string("http://schema.org/WebPage"), htmlTag->attributes["itemtype"]);
			Assert::AreEqual(string("en"), htmlTag->attributes["lang"]);

			Assert::AreEqual(string("title"), titleTag->tag_name);
			Assert::AreEqual((size_t)1, titleTag->attributes.size());
			Assert::IsTrue(titleTag->attributes.contains("data-abc"));
			Assert::AreEqual(string("123"), titleTag->attributes["data-abc"]);

			Assert::AreEqual(string("body"), bodyTag->tag_name);
			Assert::AreEqual((size_t)1, bodyTag->attributes.size());
			Assert::IsTrue(bodyTag->attributes.contains("class"));
			Assert::AreEqual(string("abc 123"), bodyTag->attributes["class"]);

			Assert::AreEqual(string("h1"), h1Tag->tag_name);
			Assert::AreEqual((size_t)1, h1Tag->attributes.size());
			Assert::IsTrue(h1Tag->attributes.contains("disabled"));
			Assert::AreEqual(string(""), h1Tag->attributes["disabled"]);

			Assert::AreEqual(string("p"), pTag->tag_name);
			Assert::AreEqual((size_t)2, pTag->attributes.size());
			Assert::IsTrue(pTag->attributes.contains("id"));
			Assert::IsTrue(pTag->attributes.contains("class"));
			Assert::AreEqual(string("test-id"), pTag->attributes["id"]);
			Assert::AreEqual(string("amazing text"), pTag->attributes["class"]);
		}
	};
}