#include "pch.h"
#include "CppUnitTest.h"

#include <string>
#include <fstream>

#include <HTMLDocument.h>
#include <HTMLNode.h>
#include <HTMLSelector.h>

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
		TEST_METHOD(MismatchedEndTags)
		{
			ifstream file("..\\..\\HTMLFiles\\mismatched-end-tags.html");
			Assert::IsTrue(file.is_open());
			HTMLDocument doc;
			doc.parse(file);

			/*
			
				The malformed HTML here should be interpreted as
				<!DOCTYPE html>[0]
				<html>[1]
					<head>[1][0]
						<title></title>[1][0][0]
					</head>
					<body>[1][1]
						<div>[1][1][0]
							<span>Hello world!</span>[1][1][0][0]
							<p>This is a paragraph!</p>[1][1][0][1]
						</div>
						<h1>This is a heading!</h1>[1][1][1]
					</body>
				</html>
				<!-- (comment explaining this) -->
			*/

			auto htmlTag = doc.root->children[1];
			auto bodyTag = htmlTag->children[1];
			auto divTag = bodyTag->children[0];

			// I've found it's actually sort of difficult to come up with
			// a test case for validating invalid input. Maybe revisit this
			// in the future?
			Assert::AreEqual((size_t)2, bodyTag->children.size());
			Assert::AreEqual((size_t)2, divTag->children.size());
		}
		TEST_METHOD(SiblingMethods)
		{
			HTMLDocument doc;
			
			auto firstElement = shared_ptr<HTMLNode>(HTMLNode::element());
			auto secondElement = shared_ptr<HTMLNode>(HTMLNode::element());

			firstElement->tag_name = "title";
			secondElement->tag_name = "body";

			doc.root->append_child(firstElement);
			doc.root->append_child(secondElement);

			// shared_ptr doesn't like being put into a temp object :(
			auto result = firstElement->prev_sibling();
			Assert::IsFalse((bool)result);
			result = secondElement->next_sibling();
			Assert::IsFalse((bool)result);

			result = secondElement->prev_sibling();
			Assert::IsTrue(firstElement == result);
			result = firstElement->next_sibling();
			Assert::IsTrue(secondElement == result);

			auto thirdElement = shared_ptr<HTMLNode>(HTMLNode::comment());
			doc.root->append_child(thirdElement);

			result = secondElement->next_sibling();
			Assert::IsFalse((bool)result);

			auto fourthElement = shared_ptr<HTMLNode>(HTMLNode::element());
			fourthElement->tag_name = "h2";
			doc.root->append_child(fourthElement);

			result = secondElement->next_sibling();
			Assert::IsTrue((bool)result);
			Assert::AreEqual(string("h2"), result->tag_name);
		}
		TEST_METHOD(CachedValueId)
		{
			HTMLNode node;
			node.attributes.insert({ "id", "abc123" });

			// First time, it is read from attribtutes array
			Assert::AreEqual(string("abc123"), node.id().value());
			// Second time, it is not
			Assert::AreEqual(string("abc123"), node.id().value());
		}
		TEST_METHOD(IdIsInsensitive)
		{
			HTMLNode node;
			node.attributes.insert({ "iD", "abc123" });

			Assert::AreEqual(string("abc123"), node.id().value());
		}
		TEST_METHOD(ClassList)
		{
			HTMLNode node;
			node.attributes.insert({ "class", "m-0 p-3 text-warning" });

			Assert::IsTrue(node.classes()->contains("m-0"));
			Assert::IsTrue(node.classes()->contains("p-3"));
			Assert::IsTrue(node.classes()->contains("text-warning"));
			// Case-insensitive?
			Assert::IsTrue(node.classes()->contains("text-WArning"));
			// You're not just saying yes to everything, are you?
			Assert::IsFalse(node.classes()->contains("text-"));
		}
		TEST_METHOD(HTMLSelectorSingleNode)
		{
			auto node = shared_ptr<HTMLNode>(HTMLNode::element());
			node->attributes.insert({ "id", "abc123" });
			node->attributes.insert({ "class", "text-warning mb-0" });
			node->attributes.insert({ "data-title", "hello world" });

			HTMLSelector selector;

			HTMLSelectorRule idRule;
			idRule.id = "abc123";
			selector.rules.push_back(idRule);

			HTMLSelectorRule classRule;
			classRule.class_names.insert("text-warning");
			classRule.class_names.insert("mb-0");
			selector.rules.push_back(classRule);

			HTMLSelectorRule classRuleNoMatch;
			classRuleNoMatch.class_names.insert("does-not-exist");

			HTMLSelectorRule attributeNameOnly;
			AttributeRequirement attributeNameOnlyReq;
			attributeNameOnly.attributes.insert({ "data-title", attributeNameOnlyReq });
			selector.rules.push_back(attributeNameOnly);

			HTMLSelectorRule attributeIns;
			AttributeRequirement attributeInsReq;
			attributeInsReq.value = "hello WORLD";
			attributeInsReq.value_case_sensitive = false;
			attributeIns.attributes.insert({ "data-title", attributeInsReq });
			selector.rules.push_back(attributeIns);

			HTMLSelectorRule attributeNoMatch;
			AttributeRequirement attributeNoMatchReq;
			attributeNoMatchReq.value = "hello WORLD";
			attributeNoMatch.attributes.insert({ "data-title", attributeNoMatchReq });

			Assert::IsTrue(idRule.is_satisfied_by(node));
			Assert::IsTrue(classRule.is_satisfied_by(node));
			Assert::IsFalse(classRuleNoMatch.is_satisfied_by(node));
			Assert::IsTrue(attributeNameOnly.is_satisfied_by(node));
			Assert::IsTrue(attributeIns.is_satisfied_by(node));
			Assert::IsFalse(attributeNoMatch.is_satisfied_by(node));

			Assert::IsTrue(selector.is_satisfied_by(node));
			// Now invalidate it and run again to assert false
			selector.rules.push_back(classRuleNoMatch);
			Assert::IsTrue(selector.is_satisfied_by(node));
		}
	};
}