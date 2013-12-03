#include <functional>
#include <algorithm>
#include <iterator>
#include <vector>

using std::vector;
 
template <typename BidirectionalIterator, typename Compare>
void quick_sort( BidirectionalIterator first, BidirectionalIterator last, Compare cmp) {
	if(first != last){
		BidirectionalIterator left  = first;
		BidirectionalIterator right = last;
		BidirectionalIterator pivot = left++;

		while(left != right) {
			if( cmp(*left, *pivot)) {
				++left;
			} else {
				while((left != right) && cmp(*pivot, *right)){
					--right;
				}
				std::iter_swap(left, right);
			}
		}

		--left;
		std::iter_swap(pivot, left);

		quick_sort(first, left, cmp);
		quick_sort(right, last, cmp);
	}
}

template <typename BidirectionalIterator, typename Compare>
void quick_sort( BidirectionalIterator first, BidirectionalIterator last, Compare cmp, vector<unsigned>::iterator firstInd, vector<unsigned>::iterator lastInd){
	if(first != last){
		BidirectionalIterator left  = first;
		BidirectionalIterator right = last;
		BidirectionalIterator pivot = left++;
		vector<unsigned>::iterator leftInd  = firstInd;
		vector<unsigned>::iterator rightInd = lastInd;
		vector<unsigned>::iterator pivotInd = leftInd++;


		while(left != right){
			if(cmp(*left, *pivot)){
				++left;
				++leftInd;
			} else {
				while((left != right) && cmp(*pivot, *right)){
					--right;
					--rightInd;
				}
				std::iter_swap(left, right);
				unsigned aux = *leftInd;
				*leftInd = *rightInd;
				*rightInd = aux;
			}
		}

		--left;
		--leftInd;
		std::iter_swap(pivot, left);
		std::iter_swap(pivotInd,leftInd);

		quick_sort(first, left, cmp,firstInd,leftInd);
		quick_sort(right, last, cmp,rightInd,lastInd);
    }
}

template <typename BidirectionalIterator>
	inline void qsort(BidirectionalIterator first, BidirectionalIterator last, vector<unsigned>::iterator firstInd, vector<unsigned>::iterator lastInd){
		quick_sort(first,last,std::less_equal<typename std::iterator_traits< BidirectionalIterator>::value_type >(),
			firstInd,lastInd);
}

template <typename BidirectionalIterator>
	inline void quick_sort( BidirectionalIterator first, BidirectionalIterator last) {
		quick_sort( first, last,
		std::less_equal<typename std::iterator_traits< BidirectionalIterator>::value_type >());
}
