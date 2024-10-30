# 电影推送系统

- C, WinAPI; 图文界面和操作, 电影介绍, 不同情景电影推荐)

- 详细的介绍见solution.docx，其它参见Readme_1.txt和Readme_2.txt

# 资源
- C语言API编写窗体界面和按钮.txt
- 类型.txt
- Movie-Recommendation-System\History_version\6.19\Windows_API，十几个示例

# Solution.docx
两部分：供用户使用和供后台人员查看用户使用情况和数据分析

一.用户
1.名称
2.密码
3.历史记录(一个图表记录所有的历史记录分析)
4.个人偏好(喜欢看的电影类别,心情)
5.修改密码
6.电影评分+评论
7.分享电影(微信,微博)
二.电影名
1.电影名
2.电影类别
喜剧 爱情 动作 动画 青春 武侠 科幻 惊悚 犯罪
3.适合心情
   高兴 激动 自豪 伤心 愤怒 害怕 羞愧 忐忑
4.专家评分
5.用户评分
6.影评(text)
5.电影信息(大小、清晰度(1080p/720p/mkv/)、下载地址、对应BT文件，下载的文件)


后台分析和管理系统
修改文本框：
1.	电影切换
矩形，右边有按钮，按下后选择可在下方显示，
可以搜索，或者输入号码，电影之前修改信息(在什么时候生成的)
2.	电影信息显示，中等大小文本框，显示各种信息，逐行显示
评论每页显示n条，评论可选择 ，用button(显示在上方,如视频网站选择看的集数)
	ES_AUTOHSCROLL 当输入文字超出横向显示范围时自动滚动

左上方有选项 供选择 看什么类别的电影，心情如何，状态如何


电影评分+点评	

用户种子分享

推荐网站：	豆瓣电影	https://movie.douban.com/
				射手字幕网	http://shooter.cn/sub/upload.html
				

所需软件：	codeblocks
				Thunder

````
    //心情
    static HWND labMood;
    static HWND radioHappy;
    static HWND radioExcited;
    static HWND radioProud;     //爱国片
    static HWND radioSad;       //
    static HWND radioAngry;     //
    static HWND radioScared;    //家庭温馨片
    static HWND radioshamed;   //羞愧


````


