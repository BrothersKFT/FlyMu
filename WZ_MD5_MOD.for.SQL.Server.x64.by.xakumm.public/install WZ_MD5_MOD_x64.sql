USE [master]

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[XP_MD5_EncodeKeyVal]') and OBJECTPROPERTY(id, N'IsExtendedProc') = 1)
	exec sp_dropextendedproc N'[dbo].[XP_MD5_EncodeKeyVal]'

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[XP_MD5_EncodeString]') and OBJECTPROPERTY(id, N'IsExtendedProc') = 1)
	exec sp_dropextendedproc N'[dbo].[XP_MD5_EncodeString]'

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[XP_MD5_CheckValue]') and OBJECTPROPERTY(id, N'IsExtendedProc') = 1)
	exec sp_dropextendedproc N'[dbo].[XP_MD5_CheckValue]'

exec sp_addextendedproc N'XP_MD5_EncodeKeyVal', N'WZ_MD5_MOD_x64.dll'
exec sp_addextendedproc N'XP_MD5_EncodeString', N'WZ_MD5_MOD_x64.dll'
exec sp_addextendedproc N'XP_MD5_CheckValue',   N'WZ_MD5_MOD_x64.dll'
