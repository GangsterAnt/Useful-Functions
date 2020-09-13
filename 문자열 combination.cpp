//디폴트 매개변수 temp 와 k 를 사용하므로써 외부벡터 combination 에 깊이 depth 만큼의 dfs 를 통해 조합을 만들어준다.

void Combination(int k = 0, string temp = "") {
    for (int i = k; i < depth; i++) {
        temp += to_string(i);
        combination.push_back(temp);
        Combination(i + 1, temp);
        temp = temp.substr(0, temp.length() - 1);
    }
}
