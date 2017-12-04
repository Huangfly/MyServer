--***************************************************
--**			�����ʷ��
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
--**			����
--***************************************************

--***************************
--**
--**    �û�Ȩ��     
--**
--***************************

--role ��ɫ��
CREATE TABLE Tbl_role
(
	role_id 					INTEGER 				primary key AUTOINCREMENT,--��ɫID
	role_name 				VARCHAR(30) 		not null,--��ɫ��
	role_remark 			VARCHAR(100)--��ע
);

--user_role �û���ɫ��
CREATE TABLE Tbl_user_role
(
	user_id 					INTEGER 				primary key AUTOINCREMENT,--�û�ID
	role_id 					INTEGER 				not null--��ɫID
);

--class ��������
CREATE TABLE Tbl_class
(
	class_id 					INTEGER 				primary key AUTOINCREMENT,--����ID
	class_name 					VARCHAR(30) 			not null--��������
);

--root ��ɫȨ�ޱ�
CREATE TABLE Tbl_root
(
	role_id 					INTEGER 				not null,--��ɫID
	menu_id 					INTEGER 				not null--�˵�ID
);

--user �û���
CREATE TABLE Tbl_user
(
	user_id 					INTEGER 				primary key AUTOINCREMENT,--�û�ID
	user_name 				VARCHAR(10) 		not null,--�û���½��
	user_password 		VARCHAR(10) 			not null,--�û���¼����
	user_type 				VARCHAR(10) 				not null,--�û���������
	user_stu 					CHAR(1) 				not null,--�û�״̬
	user_remark 			VARCHAR(100)--��ע
);

--menu �˵���
CREATE TABLE Tbl_menu
(
	menu_id 					INTEGER 				primary key AUTOINCREMENT,--�˵�ID
	menu_name 				VARCHAR(30) 		not null,--�˵���
	parent_id 				INTEGER 				not null,--�����˵�ID
	menu_stu 					CHAR(1) 				not null,--�˵�״̬
	menu_remark 			VARCHAR(100)--��ע
);


--***************************
--**
--**    �ͻ����û���Ϣ     
--**
--***************************
--client �ͻ����û�
CREATE TABLE Tbl_client
(
	client_id 				INTEGER 				primary key AUTOINCREMENT,--�û�ID
	client_name 			VARCHAR(20) 			not null,--�û���¼����
	client_password 		VARCHAR(10)				not null,--�û���¼����
	login_time				VARCHAR(20)				not null,--�û�����¼ʱ��
	client_stu 				CHAR(1) 				not null,--�û�״̬
	client_remark 			VARCHAR(100)--��ע
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


--record �û��㲥��¼
CREATE TABLE Tbl_record
(
	record_id 				INTEGER 				primary key AUTOINCREMENT,--��¼ID
	user_id 				INTEGER 				not null,--�û�ID
	video_id 				INTEGER 				not null,--��ƵID
	play_times 				INTEGER 				not null,--����ʱ��
	end_time				VARCHAR(23)				not null
);


--***************************
--**
--**    ��Ƶ��Ϣ     
--**
--***************************

--////////////////////////////////////////////////////////
--Vtype_detail  ��Ƶ������ϸ
CREATE TABLE Tbl_Vtype_detail
(
	detail_id 					INTEGER 				primary key AUTOINCREMENT,--��ϸID
	video_id 					INTEGER 				not null,--��ƵID
	type_id 					INTEGER 				not null--����ID
);

--////////////////////////////////////////////////////////
--video_channel  ��ƵƵ��
CREATE TABLE Tbl_video_channel
(
	channel_id 					INTEGER 				primary key AUTOINCREMENT,--Ƶ��ID
	channel_name 				VARCHAR(20) 			not null--Ƶ������
);

INSERT INTO Tbl_video_channel 					VALUES(1,'��Ӱ');
INSERT INTO Tbl_video_channel 					VALUES(null,'���Ӿ�');
INSERT INTO Tbl_video_channel 					VALUES(null,'����');

--////////////////////////////////////////////////////////
--video_region  ��Ƶ����
CREATE TABLE Tbl_video_region
(
	region_id 					INTEGER 				primary key AUTOINCREMENT,--����ID
	channel_id					INTEGER					not null,--Ƶ��ID
	region_name					VARCHAR(20)				not null--��������
);

INSERT INTO Tbl_video_region 					VALUES(1,1,"ŷ��");
INSERT INTO Tbl_video_region 					VALUES(2,1,"��̨");
INSERT INTO Tbl_video_region 					VALUES(3,2,"��̨");
INSERT INTO Tbl_video_region 					VALUES(4,2,"�պ�");
INSERT INTO Tbl_video_region 					VALUES(5,2,"����");
INSERT INTO Tbl_video_region 					VALUES(6,3,"����");
INSERT INTO Tbl_video_region 					VALUES(7,3,"ŷ��");
INSERT INTO Tbl_video_region 					VALUES(8,3,"�պ�");

--////////////////////////////////////////////////////////
--video_type  ��Ƶ����
CREATE TABLE Tbl_video_type
(
	type_id 					INTEGER 				primary key AUTOINCREMENT,--����ID
	channel_id					INTEGER					not null,--Ƶ��ID
	type_name 					VARCHAR(20) 			not null--��������
);

--��Ӱ
INSERT INTO Tbl_video_type 					VALUES(1,1,'����');
INSERT INTO Tbl_video_type 					VALUES(2,1,'ս��');
INSERT INTO Tbl_video_type 					VALUES(3,1,'����');
--���Ӿ�
INSERT INTO Tbl_video_type 					VALUES(4,2,'����');
INSERT INTO Tbl_video_type 					VALUES(5,2,'��ս');
INSERT INTO Tbl_video_type 					VALUES(6,2,'����');
--����
INSERT INTO Tbl_video_type 					VALUES(7,3,'��Ц');
INSERT INTO Tbl_video_type 					VALUES(8,3,'����');

--////////////////////////////////////////////////////////
--video_info  ��Ƶ��Ϣ
CREATE TABLE Tbl_video_info
(
	video_id 					INTEGER 				primary key AUTOINCREMENT,--��ƵID
	channel_id 					INTEGER 				not null,--Ƶ��ID
	region_id 					INTEGER					not null,--����ID
	type_id 					INTEGER					not null,--����ID
	video_name					VARCHAR(40)				not null,--��Ƶ����
	play_times					INTEGER					not null,
	online						CHAR(1)					not null--��������
);

INSERT INTO Tbl_video_info 					VALUES(1,3,7,8,"����ʷ����",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(2,3,6,7,"�ܳ�û",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(3,3,8,7,"����С��",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(4,1,1,2,"�𵯲���",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(5,1,1,1,"˹�ʹ�300��ʿ",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(6,1,1,3,"��ʮ�Ȼ�",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(7,1,2,1,"�Ի�����",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(8,1,2,1,"��ȭ",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(9,1,2,1,"��������",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(10,2,3,6,"��������",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(11,2,3,6,"Ǳ�оѻ�",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(12,2,3,6,"ʹͽ����",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(13,2,4,4,"�̳�����",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(14,2,4,4,"�������ǵ���",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(15,2,4,4,"ƥŵ��",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(16,2,5,5,"ѩ��",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(17,2,5,5,"����",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(18,2,5,6,"haha",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(19,3,6,7,"����A��",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(20,3,6,8,"������",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(21,3,6,8,"��Ӱ����",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(22,3,7,8,"����",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(23,3,8,8,"�������",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(24,3,8,8,"�������2",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(25,3,8,8,"�������3",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(26,3,8,8,"�������4",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(27,3,8,8,"�������5",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(28,3,8,8,"�������6",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(29,3,8,8,"�������7",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(30,3,8,8,"�������8",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(31,3,8,8,"�������9",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(32,3,8,8,"�������10",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(33,3,8,8,"�������11",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(34,3,8,8,"�������12",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(35,3,8,8,"�������13",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(36,3,8,8,"�������14",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(37,3,8,8,"�������15",0,"Y");
INSERT INTO Tbl_video_info 					VALUES(38,3,8,8,"�������16",0,"Y");



--order_type  ��Ƶ����ʽ
CREATE TABLE Tbl_order_type
(
	order_id					INTEGER 				primary key AUTOINCREMENT,--����ʽID
	order_name 					VARCHAR(20)				not null--����ʽ����
);

--system  ϵͳ��������
CREATE TABLE Tbl_system
(
	protect_time 					VARCHAR(10)				not null,--��Ļ����ʱ��
	state							CHAR(1)					not null--״̬
);

--**************************************************************
--**						��ʼ������
--**************************************************************
--��ʼ����ɫ
INSERT INTO Tbl_role VALUES(1,'ϵͳ����Ա','nothing');--1Ϊ����Ա
INSERT INTO Tbl_role VALUES(null,'ҵ�����Ա','nothing');--2Ϊҵ�����Ա
INSERT INTO Tbl_role VALUES(null,'����Ա','nothing');--3Ϊ����Ա
--��ʼ������
INSERT INTO Tbl_class VALUES(1,'���»�');
INSERT INTO Tbl_class VALUES(null,'������');
INSERT INTO Tbl_class VALUES(null,'���۲�');
INSERT INTO Tbl_class VALUES(null,'���ڲ�');

--��ʼ���û�
INSERT INTO Tbl_user 					VALUES(1001,'admin','123456','���»�','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1001,1);
INSERT INTO Tbl_user 					VALUES(null,'Neymar','666666','���۲�','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1002,2);
INSERT INTO Tbl_user 					VALUES(null,'Messi','666666','������','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1003,3);
INSERT INTO Tbl_user 					VALUES(null,'Xavi','666666','������','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1004,2);
INSERT INTO Tbl_user 					VALUES(null,'Iniesta','666666','���۲�','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1005,2);
INSERT INTO Tbl_user 					VALUES(null,'Pique','666666','���۲�','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1006,2);
INSERT INTO Tbl_user 					VALUES(null,'Suarez','666666','���۲�','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1007,2);
INSERT INTO Tbl_user 					VALUES(null,'Ronaldo','666666','���۲�','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1008,2);
INSERT INTO Tbl_user 					VALUES(null,'Bale','666666','���۲�','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1009,2);
INSERT INTO Tbl_user 					VALUES(null,'Ag��ero','666666','���۲�','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1010,2);
INSERT INTO Tbl_user 					VALUES(null,'Zhengzhi','666666','���۲�','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1011,2);
INSERT INTO Tbl_user 					VALUES(null,'Robben','666666','���۲�','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1012,2);
INSERT INTO Tbl_user 					VALUES(null,'M��ller','666666','���۲�','Y','nothing');
INSERT INTO Tbl_user_role 		VALUES(1013,2);
--��ʼ���˵�
INSERT INTO Tbl_menu 					VALUES(1,'ϵͳ����',0,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(2,'�ͻ��˹���',0,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(3,'��Ƶ����',0,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(4,'����ͳ��',0,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(5,'�˳���¼',0,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'��֯��������',1,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'�û�����',1,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'ϵͳ��������',1,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'�ͻ����û�����',2,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'�û��㲥����',2,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'Ƶ����Ϣ����',3,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'������Ϣ����',3,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'������Ϣ����',3,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'��Ƶ��Ϣ����',3,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'�㲥�������',4,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'ע��',5,'Y','nothing');
INSERT INTO Tbl_menu 					VALUES(null,'�˳�',5,'Y','nothing');

--��ʼ���˵���Ȩ��
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




--��ʼ��ϵͳ����
INSERT INTO Tbl_system VALUES('10','N');
INSERT INTO Tbl_system VALUES('20','Y');
INSERT INTO Tbl_system VALUES('25','N');
INSERT INTO Tbl_system VALUES('����','N');
--****************************************************************************
--**					������ͼ
--****************************************************************************



--**************************************************
--**		��ʾ��ͼ
--**************************************************
--SELECT * FROM view_user;
--SELECT * FROM view_menu;
