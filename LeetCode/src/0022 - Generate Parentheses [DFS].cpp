class Solution {
    struct node {
        string list;
        int leftcount;
        int rightcount;
        node() : list("("), leftcount(1), rightcount(0) {}
        node(string list, int leftcount, int rightcount) : list(list), leftcount(leftcount), rightcount(rightcount) {}

        node getLeft() {
            return node(list + "(", leftcount + 1, rightcount);
        }
        node getRight() {
            return node(list + ")", leftcount, rightcount + 1);
        }
    };
public:
    vector<string> generateParenthesis(int n) {
        stack<node> open;
        vector<string> close;

        open.push(node());
        while (!open.empty()) {
            node temp = open.top();
            open.pop();
            if (temp.leftcount > temp.rightcount)
                open.push(temp.getRight());
            if (temp.leftcount < n)
                open.push(temp.getLeft());
            if (temp.leftcount == n && temp.rightcount == n)
                close.emplace_back(temp.list);
        }

        return close;
    }
};
