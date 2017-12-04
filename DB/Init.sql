--***************************************************
--**			清空历史表
--***************************************************

DROP TABLE IF EXISTS Tbl_role;
DROP TABLE IF EXISTS Tbl_user_role;
DROP TABLE IF EXISTS Tbl_class;
DROP TABLE IF EXISTS Tbl_root;
DROP TABLE IF EXISTS Tbl_user;
DROP TABLE IF EXISTS Tbl_menu;
DROP TABLE IF EXISTS Tbl_client;
DROP TABLE IF EXISTS Tbl_record;
DROP TABLE IF EXISTS Tbl_video_type;
DROP TABLE IF EXISTS Tbl_Vtype_detail;
DROP TABLE IF EXISTS Tbl_video_channel;
DROP TABLE IF EXISTS Tbl_video_region;
DROP TABLE IF EXISTS Tbl_video_info;
DROP TABLE IF EXISTS Tbl_Vplay_detail;
DROP TABLE IF EXISTS Tbl_order_type;
DROP TABLE IF EXISTS Tbl_system;

--***************************************************
--**			创建
--***************************************************

--***************************
--**
--**    用户权限     
--**
--***************************

--role 角色表
CREATE TABLE Tbl_role
(
	role_id 					INTEGER 				primary key AUTOINCREMENT,--角色ID
	role_name 				VARCHAR(30) 		not null,--角色名
	role_remark 			VARCHAR(100)--备注
);

--user_role 用户角色表
CREATE TABLE Tbl_user_role
(
	user_id 					INTEGER 				primary key AUTOINCREMENT,--用户ID
	role_id 					INTEGER 				not null--角色ID
);

--class 所属部门
CREATE TABLE Tbl_class
(
	class_id 					INTEGER 				primary key AUTOINCREMENT,--部门ID
	class_name 					VARCHAR(30) 			not null--部门名称
);

--root 角色权限表
CREATE TABLE Tbl_root
(
	role_id 					INTEGER 				not null,--角色ID
	menu_id 					INTEGER 				not null--菜单ID
);

--user 用户表
CREATE TABLE Tbl_user
(
	user_id 					INTEGER 				primary key AUTOINCREMENT,--用户ID
	user_name 				VARCHAR(10) 		not null,--用户登陆名
	user_password 		VARCHAR(10) 			not null,--用户登录密码
	user_type 				VARCHAR(10) 				not null,--用户所属部门
	user_stu 					CHAR(1) 				not null,--用户状态
	user_remark 			VARCHAR(100)--备注
);

--menu 菜单表
CREATE TABLE Tbl_menu
(
	menu_id 					INTEGER 				primary key AUTOINCREMENT,--菜单ID
	menu_name 				VARCHAR(30) 		not null,--菜单名
	parent_id 				INTEGER 				not null,--父级菜单ID
	menu_stu 					CHAR(1) 				not null,--菜单状态
	menu_remark 			VARCHAR(100)--备注
);


--***************************
--**
--**    客户端用户信息     
--**
--***************************
--client 客户端用户
CREATE TABLE Tbl_client
(
	client_id 				INTEGER 				primary key AUTOINCREMENT,--用户ID
	client_name 			VARCHAR(20) 			not null,--用户登录名称
	client_password 		VARCHAR(10)				not null,--用户登录密码
	login_time				VARCHAR(20)				not null,--用户最后登录时间
	client_stu 				CHAR(1) 				not null,--用户状态
	client_remark 			VARCHAR(100)--备注
);

INSERT INTO Tbl_client 					VALUES(1001,'admin','123456','11:50','Y','nothing');
INSERT INTO Tbl_client 					VALUES(null,'aaa','666666','11:50','Y','nothing');
INSERT INTO Tbl_client 					VALUES(null,'bbb','666666','11:50','Y','nothing');
INSERT INTO Tbl_client 					VALUES(null,'ccc','888888','11:50','Y','nothing');
INSERT INTO Tbl_client 					VALUES(null,'ddd','888888','11:50','Y','nothing');
INSERT INTO Tbl_client 					VALUES(null,'eee','888888','11:50','Y','nothing');
INSERT INTO Tbl_client 					VALUES(null,'fff','888888','11:50','Y','nothing');
INSERT INTO Tbl_client 					VALUES(null,'ggg','888888','11:50','Y','nothing');
INSERT INTO Tbl_client 					VALUES(null,'hhh','888888','11:50','Y','nothing');
INSERT INTO Tbl_client 					VALUES(null,'iii','888888','11:50','Y','nothing');


--record 用户点播记录
CREATE TABLE Tbl_record
(
	record_id 				INTEGER 				primary key AUTOINCREMENT,--记录ID
	user_id 				INTEGER 				not null,--用户ID
	video_id 				INTEGER 				not null,--视频ID
	play_times 				INTEGER 				not null,--播放时长
	end_time				VARCHAR(23)				not null
);


--***************************
--**
--**    视频信息     
--**
--***************************

--////////////////////////////////////////////////////////
--Vtype_detail  视频分类明细
CREATE TABLE Tbl_Vtype_detail
(
	detail_id 					INTEGER 				primary key AUTOINCREMENT,--明细ID
	video_id 					INTEGER 				not null,--视频ID
	type_id 					INTEGER 				not null--分类ID
);

--////////////////////////////////////////////////////////
--video_channel  视频频道
CREATE TABLE Tbl_video_channel
(
	channel_id 					INTEGER 				primary key AUTOINCREMENT,--频道ID
	channel_name 				VARCHAR(20) 			not null--频道名称
);

INSERT INTO Tbl_video_channel 					VALUES(1,'电影');
INSERT INTO Tbl_video_channel 					VALUES(null,'电视剧');
INSERT INTO Tbl_video_channel 					VALUES(null,'动漫');

--////////////////////////////////////////////////////////
--video_region  视频地区
CREATE TABLE Tbl_video_region
(
	region_id 					INTEGER 				primary key AUTOINCREMENT,--地区ID
	channel_id					INTEGER					not null,--频道ID
	region_name					VARCHAR(20)				not null--地区名称
);

INSERT INTO Tbl_video_region 					VALUES(1,1,"欧美");
INSERT INTO Tbl_video_region 					VALUES(2,1,"港台");
INSERT INTO Tbl_video_region 					VALUES(3,2,"港台");
INSERT INTO Tbl_video_region 					VALUES(4,2,"日韩");
INSERT INTO Tbl_video_region 					VALUES(5,2,"国产");
INSERT INTO Tbl_video_region 					VALUES(6,3,"国产");
INSERT INTO Tbl_video_region 					VALUES(7,3,"欧美");
INSERT INTO Tbl_video_region 					VALUES(8,3,"日韩");

--////////////////////////////////////////////////////////
--video_type  视频分类
CREATE TABLE Tbl_video_type
(
	type_id 					INTEGER 				primary key AUTOINCREMENT,--分类ID
	channel_id					INTEGER					not null,--频道ID
	type_name 					VARCHAR(20) 			not null--分类名称
);

--电影
INSERT INTO Tbl_video_type 					VALUES(1,1,'动作');
INSERT INTO Tbl_video_type 					VALUES(2,1,'战争');
INSERT INTO Tbl_video_type 					VALUES(3,1,'爱情');
--电视剧
INSERT INTO Tbl_video_type 					VALUES(4,2,'浪漫');
INSERT INTO Tbl_video_type 					VALUES(5,2,'抗战');
INSERT INTO Tbl_video_type 					VALUES(6,2,'生活');
--动漫
INSERT INTO Tbl_video_type 					VALUES(7,3,'搞笑');
INSERT INTO Tbl_video_type 					VALUES(8,3,'剧情');

--////////////////////////////////////////////////////////
--video_info  视频信息
CREATE TABLE Tbl_video_info
(
	video_id 					INTEGER 				primary key AUTOINCREMENT,--视频ID
	channel_id 					INTEGER 				not null,--频道ID
	region_id 					INTEGER					not null,--地区ID
	type_id 					INTEGER					not null,--分类ID
	video_name					VARCHAR(40)				not null,--视频名称
	play_times					INTEGER					not null,
	online						CHAR(1)					not null--最新上线
);

INSERT INTO Tbl_video_info 					VALUES(1,3,7,8,"怪物史莱克",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(2,3,6,7,"熊出没",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(3,3,8,7,"蜡笔小新",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(4,1,1,2,"拆弹部队",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(5,1,1,1,"斯巴达300勇士",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(6,1,1,3,"五十度灰",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(7,1,2,1,"卧虎藏龙",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(8,1,2,1,"醉拳",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(9,1,2,1,"功夫足球",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(10,2,3,6,"冲上云霄",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(11,2,3,6,"潜行狙击",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(12,2,3,6,"使徒行者",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(13,2,4,4,"继承者们",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(14,2,4,4,"来自星星的你",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(15,2,4,4,"匹诺曹",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(16,2,5,5,"雪豹",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(17,2,5,5,"亮剑",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(18,2,5,6,"haha",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(19,3,6,7,"哆来A梦",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(20,3,6,8,"海贼王",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(21,3,6,8,"火影忍者",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(22,3,7,8,"超人",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(23,3,8,8,"忍者神龟",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(24,3,8,8,"忍者神龟2",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(25,3,8,8,"忍者神龟3",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(26,3,8,8,"忍者神龟4",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(27,3,8,8,"忍者神龟5",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(28,3,8,8,"忍者神龟6",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(29,3,8,8,"忍者神龟7",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(30,3,8,8,"忍者神龟8",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(31,3,8,8,"忍者神龟9",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(32,3,8,8,"忍者神龟10",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(33,3,8,8,"忍者神龟11",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(34,3,8,8,"忍者神龟12",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(35,3,8,8,"忍者神龟13",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(36,3,8,8,"忍者神龟14",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(37,3,8,8,"忍者神龟15",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(38,3,8,8,"忍者神龟16",0,"Y");



--order_type  视频排序方式
CREATE TABLE Tbl_order_type
(
	order_id					INTEGER 				primary key AUTOINCREMENT,--排序方式ID
	order_name 					VARCHAR(20)				not null--排序方式名称
);

--system  系统参数设置
CREATE TABLE Tbl_system
(
	protect_time 					VARCHAR(10)				not null,--屏幕保护时间
	state							CHAR(1)					not null--状态
);

--**************************************************************
--**						初始化数据
--**************************************************************
--初始化角色
INSERT INTO Tbl_role VALUES(1,'系统管理员','nothing');--1为管理员
INSERT INTO Tbl_role VALUES(null,'业务管理员','nothing');--2为业务管理员
INSERT INTO Tbl_role VALUES(null,'操作员','nothing');--3为操作员
--初始化部门
INSERT INTO Tbl_class VALUES(1,'董事会');
INSERT INTO Tbl_class VALUES(null,'技术部');
INSERT INTO Tbl_class VALUES(null,'销售部');
INSERT INTO Tbl_class VALUES(null,'后勤部');

--初始化用户
INSERT INTO Tbl_user 					VALUES(1001,'admin','123456','董事会','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1001,1);
INSERT INTO Tbl_user 					VALUES(null,'Neymar','666666','销售部','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1002,2);
INSERT INTO Tbl_user 					VALUES(null,'Messi','666666','技术部','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1003,3);
INSERT INTO Tbl_user 					VALUES(null,'Xavi','666666','技术部','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1004,2);
INSERT INTO Tbl_user 					VALUES(null,'Iniesta','666666','销售部','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1005,2);
INSERT INTO Tbl_user 					VALUES(null,'Pique','666666','销售部','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1006,2);
INSERT INTO Tbl_user 					VALUES(null,'Suarez','666666','销售部','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1007,2);
INSERT INTO Tbl_user 					VALUES(null,'Ronaldo','666666','销售部','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1008,2);
INSERT INTO Tbl_user 					VALUES(null,'Bale','666666','销售部','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1009,2);
INSERT INTO Tbl_user 					VALUES(null,'Agüero','666666','销售部','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1010,2);
INSERT INTO Tbl_user 					VALUES(null,'Zhengzhi','666666','销售部','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1011,2);
INSERT INTO Tbl_user 					VALUES(null,'Robben','666666','销售部','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1012,2);
INSERT INTO Tbl_user 					VALUES(null,'Müller','666666','销售部','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1013,2);
--初始化菜单
INSERT INTO Tbl_menu 					VALUES(1,'系统管理',0,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(2,'客户端管理',0,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(3,'视频管理',0,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(4,'报表统计',0,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(5,'退出登录',0,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'组织机构管理',1,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'用户管理',1,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'系统参数设置',1,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'客户端用户管理',2,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'用户点播管理',2,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'频道信息管理',3,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'分类信息管理',3,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'地区信息管理',3,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'视频信息管理',3,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'点播报表管理',4,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'注销',5,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'退出',5,'Y','nothing');

--初始化菜单的权限
INSERT INTO Tbl_root					VALUES(1,1);
INSERT INTO Tbl_root					VALUES(1,2);
INSERT INTO Tbl_root					VALUES(1,3);
INSERT INTO Tbl_root					VALUES(1,4);
INSERT INTO Tbl_root					VALUES(1,5);
INSERT INTO Tbl_root					VALUES(2,2);
INSERT INTO Tbl_root					VALUES(2,3);
INSERT INTO Tbl_root					VALUES(2,4);
INSERT INTO Tbl_root					VALUES(2,5);
INSERT INTO Tbl_root					VALUES(3,4);
INSERT INTO Tbl_root					VALUES(3,5);




--初始化系统参数
INSERT INTO Tbl_system VALUES('10','N');
INSERT INTO Tbl_system VALUES('20','Y');
INSERT INTO Tbl_system VALUES('25','N');
INSERT INTO Tbl_system VALUES('永不','N');
--****************************************************************************
--**					创建视图
--****************************************************************************



--**************************************************
--**		显示视图
--**************************************************
--SELECT * FROM view_user;
--SELECT * FROM view_menu;
