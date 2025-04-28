DBCC WZ_MD5_MOD_x64 (FREE)

-- XP_MD5_EncodeKeyVal 
-- test script by navossoc
SET NOCOUNT ON


DECLARE @login1 char(10), @pass1 char(10), @Hash1 binary(16)
set @login1 = 'login'
set @pass1 = 'pass'


EXEC master.dbo.XP_MD5_EncodeKeyVal @login1, @pass1, @Hash1 OUT


---------------------------------------------------------------------


DECLARE @login1n nchar(10), @pass1n nchar(10), @Hash1n binary(16)
set @login1n = N'login'
set @pass1n = N'pass'


EXEC master.dbo.XP_MD5_EncodeKeyVal @login1n, @pass1n, @Hash1n OUT


---------------------------------------------------------------------


DECLARE @LogiN2 varchar(10), @pass2 varchar(10), @Hash2 binary(16)
set @LogiN2 = 'login'
set @pass2 = 'pass'


EXEC master.dbo.XP_MD5_EncodeKeyVal @LogiN2, @pass2, @Hash2 OUT


---------------------------------------------------------------------


DECLARE @LogiN2n nvarchar(10), @pass2n nvarchar(10), @Hash2n binary(16)
set @LogiN2n = N'login'
set @pass2n = N'pass'


EXEC master.dbo.XP_MD5_EncodeKeyVal @LogiN2n, @pass2n, @Hash2n OUT


---------------------------------------------------------------------


declare @Hash3 binary(16)
EXEC master.dbo.XP_MD5_EncodeKeyVal 'login', 'pass', @Hash3 OUT


---------------------------------------------------------------------


declare @Hash3n binary(16)
EXEC master.dbo.XP_MD5_EncodeKeyVal N'login', N'pass', @Hash3n OUT


---------------------------------------------------------------------


select @Hash1 as 'char', @Hash1n as 'nchar'
select @Hash2 as 'varchar', @Hash2n as 'nvarchar' 
select @Hash3 as 'literal', @Hash3n as 'nliteral'

DBCC WZ_MD5_MOD_x64 (FREE)

/*
char                               nchar
---------------------------------- ----------------------------------
0x49192D0074BA77460E1AC359D3DDEABA 0xABEF31793325B11D7DBBF98C8F3C2794


varchar                            nvarchar
---------------------------------- ----------------------------------
0x2450781554F7806EC1A4DE67E7A762C4 0xEA4C79D5CF04F00860937968F60C7EFC


literal                            nliteral
---------------------------------- ----------------------------------
0x19522F64C31DD4CB2DA20AADC2CE924D 0x2A6985F2ECB9C4F4B37439125F7B4C4E
*/