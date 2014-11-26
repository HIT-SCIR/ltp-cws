LTP分词使用文档
===============

## 目录
* [简介](#简介)
* [安装LTP分词版](#安装LTP分词版)
* [使用分词可执行程序](#使用分词可执行程序)
* [使用分词动态库](#使用分词动态库)
* [使用分词训练套件](#使用分词训练套件)

# 简介
LTP的分词模块基于结构化感知器（Structured Perceptron）算法构建，具有准确率高、速度快等优点；同时支持用户自定义词典，适应不同用户的需求；另外还新增了个性化（增量式）训练功能，用户可以根据自己的实际需求，如对新领域的文本进行分词等，自行标注少量句子的分词结果（比如对LTP分词结果的修正），LTP分词模块可以重新训练一个更好应对新领域的分词器，进一步提高新领域上分词的准确率。

分词是许多自然语言处理任务的基础，应用最为广泛。为了方便用户使用分词功能，我们把分词模块独立出来开发了LTP分词版(LTP-CWS)。

# 安装LTP分词版

##获得LTP分词版

作为安装的第一步，你需要获得LTP-CWS。LTP-CWS包括两部分，分别是项目源码和编译好的模型文件。你可以从以下链接获得最新的LTP项目源码。

* Github项目托管：[https://github.com/HIT-SCIR/ltp-cws](https://github.com/HIT-SCIR/ltp-cws)

同时，从以下链接获得LTP的**分词模型**(cws.model)。

* [百度云](http://pan.baidu.com/share/link?shareid=1988562907&uk=2738088569#path=%252Fltp-models%252F3.2.0%252Fsubmodels) （当前模型版本3.2.0）

##编译LTP-CWS

有关在不同平台下如何编译LTP-CWS，可以[参考这里](https://github.com/HIT-SCIR/ltp/blob/master/doc/ltp-document-3.0.md#开始使用ltp)

#使用分词可执行程序

编译成功后，会在./bin/文件夹下生成如下四个分词程序:

##cws_cmdline

功能：

加载模型和外部词典对输入文本进行分词。

运行命令：

    cws_cmdline model_path lexicon_path

说明：

model_path 表示模型文件的路径，lexicon_path 表示领域词典文件的路径。其中，领域词典是一个可选的参数，当用户提供领域词典时，可以保证分词结果可以把词典中的词正确切分，达到简单高效的实现正确切分某些特定词语的目的。

词典的格式为每一行一个词（注意只支持utf-8编码的中文），一个简单的金融领域词典如下所示：

    买空

    卖空

    比特币
输入输出：

输入输出为标准输入输出。

运行示例：

    cws_cmdline cws.model dict.txt <document.txt >result.txt

##multi_cws_cmdline

功能：

其功能和cws_cmdline一致，特点是支持多线程的运行。

运行命令：

    cws_cmdline model_path lexicon_path thread_num
    
说明：

前两个参数和cws_cmdline一致，thread_num表示运行的线程数。

输入输出：

输入输出为标准输入输出。

运行示例：

    cws_cmdline cws.model dict.txt 4 <document.txt >result.txt
    
另外还有两个可执行程序是otcws、otcws-customized，它们是训练套件，参加下文[使用分词训练套件](#使用分词训练套件)。



#使用分词动态库

如果您需要将分词功能动态的插入到自己的代码中，就需要使用分词动态库，LTP的动态库在lib文件夹下。
如果您之前对C++使用动态库并不熟悉，可以[参考这里](http://msdn.microsoft.com/zh-cn/library/ms235636.aspx)。

下面以一个分词程序cws.cpp来说明调用动态库的具体过程。
第一步，编写调用动态库的程序(注意需要包含头文件segment_dll.h，在include文件夹下)，代码如下：

	#include <iostream>
	#include <string>
	#include "segment_dll.h"
	
	int main(int argc, char * argv[]) {
	    if (argc < 2) {
	        std::cerr << "cws [model path]" << std::endl;
	        return 1;
	    }
	
	    void * engine = segmentor_create_segmentor(argv[1]);//分词接口，初始化分词器
	    if (!engine) {
	        return -1;
	    }
	    std::vector<std::string> words;
	    int len = segmentor_segment(engine, 
	            "爱上一匹野马，可我的家里没有草原。", words);//分词接口，对句子分词。
	    for (int i = 0; i < len; ++ i) {
	        std::cout << words[i] << "|";
	    }
	    std::cout << std::endl;
	    segmentor_release_segmentor(engine);//分词接口，释放分词器
	    return 0;
	}

第二步，编译程序，需要加入头文件segment_dll.h和动态库的路径。

下面给出Linux、Windows两个平台下的编译示例。

##Windows(MSVC)编译
1）添加头文件路径

右键工程->Configuration properties->c/c++->general->additional include directories
![include.png](http://ir.hit.edu.cn/ltp-2014/images/include.png)
2）添加动态库路径

右键工程->Configuration properties->linker->general->additional library directories
![lib.png](http://ir.hit.edu.cn/ltp-2014/images/lib.png)
3）导入所需的动态库

右键工程->properties->linker->input->additional additional dependencies，分词需添加segmentor.lib和boost_regex.lib。
![import.png](http://ir.hit.edu.cn/ltp-2014/images/import.png)

4）最后，Build工程即可。

##Linux

假定您下载并将LTP放置于/path/to/your/ltp-project路径下,那么编译命令例如下：

    g++ -o cws cws.cpp -I /path/to/your/ltp-project/include/ -I /path/to/your/ltp-project/thirdparty/boost/include -WL,-dn -L /path/to/your/ltp-project/lib/ -lsegmentor -lboost_regex -WL,-dy

## 分词接口

分词主要提供三个接口：

**void * segmentor_create_segmentor**

功能：

读取模型文件，初始化分词器。

参数：

| 参数名 | 参数描述 |
|--------|----------|
|const char * path | 指定模型文件的路径 |
|const char * lexicon_path | 指定外部词典路径。如果lexicon_path为NULL，则不加载外部词典 |

返回值：

返回一个指向分词器的指针。

**int segmentor_release_segmentor**

功能：

释放模型文件，销毁分词器。

参数：

| 参数名 | 参数描述 |
|--------|----------|
|void * segmentor | 待销毁分词器的指针 |

返回值：

销毁成功时返回0，否则返回-1

**int segmentor_segment**

功能：

调用分词接口。

参数：

| 参数名 | 参数描述 |
|--------|----------|
|void * segmentor | 分词器的指针 |
|const std::string & line | 待分词句子 |
|std::vector\<std::string\> & words| 结果分词序列 |

返回值：

返回结果中词的个数。


#使用分词训练套件

##otcws

otcws是ltp分词模型的训练套件，用户可以使用otcws训练获得ltp的分词模型。

编译之后，在tools/train下面会产生名为otcws的二进制程序。调用方法是

	./otcws [config_file]

otcws分别支持从人工切分数据中训练分词模型和调用分词模型对句子进行切分。人工切分的句子的样例如下：

	对外	，	他们	代表	国家	。

otcws主要通过配置文件指定执行的工作，其中主要有两类配置文件：训练配置和测试配置。

训练配置的配置文件样例如下所示。

	[train]
	train-file = data/ctb5-train.seg
	holdout-file = data/ctb5-holdout.seg
	algorithm = pa 
	model-name = model/ctb5-seg
	max-iter = 5
	enable-incremental-training = 0
	rare-feature-threshold = 0
	
其中，

* [train] 配置组指定执行训练
	* train-file 配置项指定训练集文件
	* holdout-file 配置项指定开发集文件
	* algorithm 指定参数学习方法，现在otcws支持两种参数学习方法，分别是passive aggressive(pa)和average perceptron(ap)。
	* model-name 指定输出模型文件名
	* max-iter 指定最大迭代次数
	* enable-incremental-training 配置输出的模型是否支持后续增量训练，enable-incremental-training为0不支持，1支持。
	* rare-feature-threshold 配置裁剪力度，如果rare-feature-threshold为0，则只去掉为0的特征；rare-feature-threshold；如果大于0时将进一步去掉更新次数低于阈值的特征

测试配置的配置文件样例如下所示。

	[test]
	test-file = data/ctb5-test.seg
	model-file = model/ctb5-seg.4.model

其中，

* [test] 配置组指定执行测试
	* test-file 指定测试文件
	* model-file 指定模型文件位置
	
切分结果将输出到标准io中。

(*[train]与[test]两个配置组不能同时存在)

## otcws-customized
otcws-customized是LTP分词模型的个性化训练套件。当用户处理一个特定领域的文本时，例如《诛仙》小说，包含大量特殊的人名、地名、武功等等，LTP的通用模型的准确效果可能并不能满足要求。为了使LTP具备这样的领域适应功能，我们开发了otcws-customized，用户只需要标注少量（500句左右）特定领域的文本，就能很好的提升效果。

otcws-customized能够在一个已经训练好的模型的基础上，继续增加特定领域的训练数据进行训练，得到一个描述该领域特性的增量模型。使用LTP的基础模型和该领域的增量模型，能够准确的预测该领域的文本。

###重要注意
只有版本在3.2.0以上的模型才支持增量式训练，也即在由otcws训练出时，配置项enable-incremental-training = 1。

###otcws-customized使用流程

1）增量训练

读入一个训练好的基础模型、新领域的训练数据进行增量训练。基础模型和训练数据等通过配置文件train.cnf 指定，配置项示例及含义见下面：

	[train]
	train-file = data/ctb5-inc.seg
	holdout-file = data/ctb5-holdout.seg
	baseline-model-file = model/basic.4.model
	algorithm = pa 
	customized-model-name = model/ctb5-seg-customized
	enable-incremental-training = 0
	max-iter = 5
	rare-feature-threshold = 0
其中，
* baseline-model-name 配置项指定基础模型的路径

其他配置项含义同otcws部分。

运行示例：

    otcws-customized train.cnf
2）个性化预测

读入训练好的基础模型、特定领域的增量模型进行个性化预测。基础模型、增量模型、待预测文本都由配置项指定，配置项示例及含义见下面：

	[test]
	test-file = data/ctb5-test.seg
	customized-model-file = model/ctb5-seg.4.model
	baseline-model-file = basic.4.model

其中，

	* baseline-model-file 指定基础模型的路径
其他配置项含义同otcws部分。

运行示例：

    otcws-customized test.cnf >output.txt
    
切分结果将输出到标准io中。
    
(*[train]与[test]两个配置组不能同时存在)
