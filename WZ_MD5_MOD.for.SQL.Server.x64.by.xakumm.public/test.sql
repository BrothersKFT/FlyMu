DBCC WZ_MD5_MOD_x64 (FREE)

-- XP_MD5_EncodeKeyVal
DECLARE @btInStr				VARCHAR(10)
DECLARE @btInStrIndex			VARCHAR(10)
DECLARE	@btOutVal				BINARY(16)
set @btInStr = 'login'
set @btInStrIndex = 'pass'
EXEC master..XP_MD5_EncodeKeyVal @btInStr, @btInStrIndex, @btOutVal OUT
print @btOutVal
	--result: 0x2450781554F7806EC1A4DE67E7A762C4
	
DECLARE @btInStr1				NVARCHAR(10)
DECLARE @btInStrIndex1			NVARCHAR(10)
DECLARE	@btOutVal1				BINARY(16)
set @btInStr1 = N'login'
set @btInStrIndex1 = N'pass'
EXEC master..XP_MD5_EncodeKeyVal @btInStr1, @btInStrIndex1, @btOutVal1 OUT
print @btOutVal1
	--result: 0xEA4C79D5CF04F00860937968F60C7EFC

-- XP_MD5_EncodeKeyVal
DECLARE @btInStr2				VARCHAR(10)
DECLARE @btInStrIndex2			VARCHAR(10)
DECLARE	@btOutVal2				CHAR(32)
set @btInStr2 = 'login'
set @btInStrIndex2 = 'pass'
EXEC master..XP_MD5_EncodeString @btInStr2, @btInStrIndex2, @btOutVal2 OUT
print @btOutVal2
	--result: 0x2450781554F7806EC1A4DE67E7A762C4
	
DECLARE @btInStr3				NVARCHAR(10)
DECLARE @btInStrIndex3			NVARCHAR(10)
DECLARE	@btOutVal3				CHAR(32)
set @btInStr3 = N'login'
set @btInStrIndex3 = N'pass'
EXEC master..XP_MD5_EncodeString @btInStr3, @btInStrIndex3, @btOutVal3 OUT
print @btOutVal3
	--result: 0xEA4C79D5CF04F00860937968F60C7EFC
	

-- XP_MD5_CheckValue
DECLARE @CheckValueStr				VARCHAR(10)
DECLARE @CheckValueStrIndex			VARCHAR(10)
DECLARE @CheckValueVal				BINARY(16)
DECLARE	@CheckValueOutResult		TINYINT
set @CheckValueStr = 'login'
set @CheckValueStrIndex = 'pass'
SET @CheckValueVal = 0x2450781554F7806EC1A4DE67E7A762C4
EXEC master..XP_MD5_CheckValue @CheckValueStr, @CheckValueVal, @CheckValueStrIndex, @CheckValueOutResult OUT
print 	@CheckValueOutResult
	--result: 1

DECLARE @CheckValueStr2				NVARCHAR(10)
DECLARE @CheckValueStrIndex2		NVARCHAR(10)
DECLARE @CheckValueVal2				BINARY(16)
DECLARE	@CheckValueOutResult2		TINYINT
set @CheckValueStr2 = N'login'
set @CheckValueStrIndex2 = N'pass'
SET @CheckValueVal2 = 0xEA4C79D5CF04F00860937968F60C7EFC
EXEC master..XP_MD5_CheckValue @CheckValueStr2, @CheckValueVal2, @CheckValueStrIndex2, @CheckValueOutResult2 OUT
print 	@CheckValueOutResult2
	--result: 1

DBCC WZ_MD5_MOD_x64 (FREE)