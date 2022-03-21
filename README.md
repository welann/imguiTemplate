# 一些注意点


## 最好封装了之后再用

## ❗node放置的位置❗

```c++
ImGui::Begin("node editor");
ImNodes::BeginNodeEditor();

//在这里写节点相关的内容才能显示

ImNodes::EndNodeEditor();
ImGui::End();
```
## 注意不同节点的id必须不同，因为它是依靠id来判断的
已经用过的id不能再用！！！
```c++
ImNodes::BeginNode(id);
和
ImNodes::BeginOutputAttribute(id);

```

## 需要自己判断节点之间的连接状态
```c++
ImNodes::Link(0,2,3);
//参数是这么个意思
void Link(const int id, const int start_attr_id, const int end_attr_id)

```

