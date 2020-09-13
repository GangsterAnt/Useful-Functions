void Combination(int k = 0, string temp = "") {
    for (int i = k; i < column; i++) {
        temp += to_string(i);
        combination.push_back(temp);
        Combination(i + 1, temp);
        temp = temp.substr(0, temp.length() - 1);
    }
}
