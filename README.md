### 编辑/etc/samba/smb.conf文件
```bash
[share]           #共享文件的名称， 将在网络上以此名称显示
path = /home/pi/Desktop/         #共享文件的路径，我们默认使用桌面文件夹
valid users = pi        #允许访问的用户
browseable = yes        #允许浏览
public = yes        #共享开放
writable = yes        #可写
```

### 给samba增加用户
```bash
smbpasswd -a <用户名>
```
![image](https://note.youdao.com/yws/api/personal/file/WEB9aa1c4fd389c3c4bcd0d0f10da68080c?method=download&shareKey=c06c89d9869cf7938a492ea45fc2afd6)
