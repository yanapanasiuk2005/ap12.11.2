#include "pch.h"
#include "CppUnitTest.h"
#include <cassert>
#include "../ap12.11.2/ap12.11.2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest12112
{
    TEST_CLASS(UnitTest12112)
    {
    public:

        TEST_METHOD(TestMethod1)
        {
            Node* exp = nullptr;

            initializeLibrary(exp);
            Book book = { "UDC1", "Author1", "Title1", 2021, 1 };
            Node* newNode = new Node;
            newNode->book = book;
            newNode->left = nullptr;
            newNode->right = nullptr;
            exp = newNode;

            string udc = "RHT.4T";
            removeBook(exp, "RHT.4T");

            assert(exp == nullptr);
        }
    };
}

