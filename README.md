# <font face="仿宋" color=orange>Markdown入门</font>
### 一 准备工作
1. **安装vscode**
   [下载]https://code.visualstudio.com/
2. **插件**
   - Markdown All in One
   - Markdown Preview Enhanced
   - Paste Image
### 二 基本语法
1. **标题**
   #一级标题
   ##二级标题
   ...
2. **引用**
   > 这个引用好
   >> 这个嵌套引用好
3. **列表**
   1. 无序列表
   - 列表1
   - 列表2
   2. 有序列表
   3. TodoList
      - [ ] a
      - [x] b
4. **表格**
   | 左对齐 | 中对齐 | 右对齐 |
   | :----- | :----: | ----: |
   | a | b | c |
5. **段落**
   - 换行：2个以上空格+回车/空1行
   - 分割线：3个以上*
   ***
   - 字体
     | 字体 | 代码 |
     | :--: | :--:|
     | *斜体* | * * |
     | ==高亮== | == == |
     | **粗体** | ** ** |
     | ***斜粗体*** | *** *** |
     | ~~删除~~ | ~~ ~~ |
     | <u>下划线</u> | ```<u> </u>``` |
   - 脚注
     请3连[^1]支持
6. **代码**
   ```
   #include<iostream>
   using namespace std;
   int main(){
    print("hello world");
   }
   ```
   `print("hello world")`
### 三 数学公式
   - 行内显示：$f(x)=ax+b$
   - 块内显示：
   $$
   \begin{Bmatrix}
   a & b \\
   c & d
   \end{Bmatrix}
   $$

[^1]: 点赞、投币、收藏