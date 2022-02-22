unsigned int Search (int * arr, int length, int numb) {
    for (unsigned int i = 0; i < length; i++ ) {
        if (arr[i] == numb) {
            return i;
        }
    }
    return length;
}

unsigned int Binary_Search (int * arr, int length, int numb) {
    int left = 0;
    int right = length - 1;
    while (left <= right) {
        tmp = left + (right - left)/2;
        if (arr[tmp] == numb) {
            return tmp;
        }
        if (arr[tmp] < numb) { // ищу в большей половине
            left = tmp + 1;
        }
        if (arr[tmp] > numb) { // ищу в меньшей половине
            right = tmp - 1;
        }
    }
    return length;
}
