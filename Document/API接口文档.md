# API接口文档
---
>## 一、可视化图形页面

![](/readmesrc/API_GUI.png)
本项目的可视化图形页面由.ui文件提供

其中任意控件任意信息都可以使用ui->的方式调用，例:
![](/readmesrc/useOfUi.png)

>## 二、输入信息的调用

>>### 1.1 搜索路径选择按钮的实现

搜索路径的选择主要通过***QString directory = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this,tr("save path"),QDir::currentPath()))***;
代码实现，接下来的代码都是用于把选择出的路径塞入combobox控件的。

![](/readmesrc/FileButton.png)
(代码示例)
>>### 1.2 搜索路径的调用实现

![](/readmesrc/API_combobox_Text.png)
(代码示例)

***ui->comboBox->currentText()***

可以通过该代码直接调用

>>### 2.1 文件名输入的调用实现

![](/readmesrc/API_LineEdit.png)
(代码示例)

***ui->m_inputLineEdit->text()***

>>### 3.1 文件内容输入的调用实现

![](/readmesrc/API_combobox2.png)

(代码示例)

***ui->comboBox2->currentText()***

>## 三、文件名搜索实现

>>### 1.1 搜索策略
首先软件会使用广度优先搜索(BFS)对根目录下的所有文件进行遍历，并将txt、doc、pdf文档加入到filelist中，随后将根据排序策略与匹配度进行重新排序，越满足用户需求的文件越排在上方。
![](/readmesrc/API_BFS.png)
(图中fileInfo.suffix()==""中可以添加其他后缀，这样即可将其他文件类型也加入搜索中)

>>### 2.1 非正则表达式的情况
在非正则表达式的情况下，文件名的匹配采用lcs最长公共子序列来实现，此时匹配的字符串越长，在排序中排的越前面。

![](/readmesrc/API_LCS.png)


>>### 2.2 正则表达式的情况下

在正则表达式的情况下，文件名的匹配采用QRegularExpression 匹配。

![](/readmesrc/API_QRegularExpression.png)

该函数为Qt库自带的库函数，非常好用。

>## 四、文件内容搜索的实现

软件调用搜索内容作为目标字符串，遍历filelist中存储的所有路径，打开所有文本文件对其使用KMP字符串匹配算法，若匹配到目标则返回目标前后42个字符，若未匹配目标则返回空字符串。

![](/readmesrc/API_KMP.png)

>> #### 拼音搜索的实现方案

将待匹配字符串与文章通过convertToPinyin转换为拼音，再进行kmp字符串匹配，匹配成功后返回匹配位置，将该位置前后记录下来显示在内容简介上。

![](/readmesrc/convertTopinyin.png)

>## 五、文件操作的实现

>>### 1.1 文件导出
文件导出的实现放在kfilesaver.cpp中。

![](/readmesrc/API_KfileSaver.png)

>>### 2.1 文件删除
文件导出的实现放在kfiledelete.cpp中。

![](/readmesrc/API_KfileDeleter.png)

>>### 2.2 文件删除线程

![](/readmesrc/API_KFileDeleterT.png)
(为了防止文件删除导致线程堵塞)

>>## 六、拼音搜索

拼音搜索采用开源项目,链接：https://github.com/newMoonxx/ChineseToPinyin

在项目中的kpinyin.h、kpinyin.cpp两个文件是引用的代码。

