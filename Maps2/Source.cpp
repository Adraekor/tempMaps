#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

namespace Maps
{
	template<typename T>
	struct cNode
	{
		unsigned int iIndex;
		unsigned int iPrevious;
		unsigned int iNext;
		T oData;

		cNode() {}
		cNode(unsigned int index, unsigned int next, unsigned int previous) :iIndex(index), iNext(next), iPrevious(previous) {}
	};

	template<typename T>
	std::ostream &operator<<(std::ostream &os, cNode<T> const& item) {
		return os << "Index : " << item.iIndex << " / Previous index : " << item.iPrevious << " / Next index : " << item.iNext << " / Data : " << item.oData << '\n';
	}

	bool PlaceComparator(cNode<int> const& item1, cNode<int> const& item2)
	{
		return item1.oData != item2.oData;
	}


	template<typename T>
	struct cList
	{
		std::vector<cNode<T>> vContent;

		void Add(T item)
		{
			cNode<T> node;
			node.oData = item;

			if (vContent.size() != 0)
			{
				auto newIndex = vContent.size();

				node.iIndex = newIndex;
				node.iPrevious = newIndex - 1;
				
				vContent.back().iNext = newIndex;
				vContent[0].iPrevious = newIndex;
			}
			else
			{
				node.iIndex = 0;
				node.iPrevious = 0;
			}

			node.iNext = 0;
			
			vContent.push_back(node);
		}

		cNode<T> Find(T item)
		{
			auto a = std::find_if(vContent.begin(), vContent.end(), PlaceComparator);
			return *a;
		}

		cNode<T> Remove(T item)
		{
			auto deletedItem = std::find_if(vContent.begin(), vContent.end(), PlaceComparator);
			cNode<T> copy = *deletedItem;

			vContent.erase(deletedItem);
		}
	};
}

bool IsOdd(int i) {
	return ((i % 2) == 1);
}

int main()
{
	Maps::cList<int> list;

	int i1 = 1;
	int i2 = 2;
	int i3 = 3;
	int i4 = 4;
	int i5 = 5;

	list.Add(i1);
	list.Add(i2);
	list.Add(i3);
	list.Add(i4);
	list.Add(i1);
	list.Add(i2);

	std::cout << "Start of dump\n\n";
	for (auto i : list.vContent)
		std::cout << i;

	std::cout << "\n\nEnd of dump\n\n";

	std::cout << list.Find(4) << std::endl;

	//std::vector<int> myvector;

	//myvector.push_back(10);
	//myvector.push_back(25);
	//myvector.push_back(40);
	//myvector.push_back(55);

	//std::vector<int>::iterator it = std::find_if(myvector.begin(), myvector.end(), IsOdd);
	//std::cout << "The first odd value is " << *it << '\n';

	char a;
	std::cin >> a;
}