// Copyright 2023 Nosonova Darina
#include "../../../modules/task_3/nosonova_d_double_radix_sort_tbb/nosonova_d_double_radix_sort_tbb.h"

#include <tbb/tbb.h>

#include <list>
#include <vector>

void RadixSort(DCArray* array) {
	std::vector<std::vector<convDouble>> cArr(256);
	int digit = 0;
	// first bait initialization
	for (int i = 0; i < array->size; i++) {
		int zn{ static_cast<int>(array->data[i].ch[digit]) };
		cArr.at(zn).push_back(array->data[i]);
	}

	digit++;
	for (; digit <= 7; digit++) {
		std::vector<std::vector<convDouble>> reachVector(256);
		for (int i = 0; i < 256; i++) {
			for (auto j : cArr.at(i)) {
				int zn{ static_cast<int>(j.ch[digit]) };
				reachVector.at(zn).push_back(j);
			}
		}
		cArr = reachVector;
	}
	std::list<convDouble> ResultList;
	for (int i = 0; i < 256; i++) {
		for (auto j : cArr.at(i)) {
			int zn = static_cast<int>(j.ch[7]);
			if (zn & 128)
				ResultList.push_front(j);
			else
				ResultList.push_back(j);
		}
	}

	// convertation
	int i = 0;
	for (auto it : ResultList) {
		array->data[i] = it;
		i++;
	}
}

DCArray Merge(const DCArray& left, const DCArray& right) {
	DCArray result(left.size + right.size);
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < left.size && j < right.size) {
		if (left.data[i].d < right.data[j].d) {
			result.data[k] = left.data[i];
			i++;
		}
		else {
			result.data[k] = right.data[j];
			j++;
		}
		k++;
	}
	while (i < left.size) {
		result.data[k] = left.data[i];
		k++;
		i++;
	}
	while (j < right.size) {
		result.data[k] = right.data[j];
		k++;
		j++;
	}

	return result;
}

void TBBRadixSort(DCArray* array) {
	DCArray result(0);

	tbb::spin_mutex pushMutex;
	tbb::parallel_for(tbb::blocked_range<int>(0, array->size),
		[&](tbb::blocked_range<int> r) {
			DCArray local_arr = array->getPart(r.begin(), r.end());
			RadixSort(&local_arr);

			pushMutex.lock();
			result = Merge(result, local_arr);
			pushMutex.unlock();
		});

	for (int i = 0; i < array->size; i++) {
		array->data[i] = result.data[i];
	}
}
