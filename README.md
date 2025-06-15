## Mô tả
- File chính `main.c` các thư viện nằm trong folder `lib` data được lưu trong folder `database` các file biên dịch được lưu vào foder `build`
- `Makefile` dùng để build chương trình tự động

## Hoạt động chương trình

Muốn chạy được chương trình phải download make và GCC 

### Dowload make 
Mở terminal và paste lệnh sau: 
```
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
Invoke-RestMethod -Uri https://get.scoop.sh | Invoke-Expression
```
Sau khi chạy xong chạy lệnh tiếp theo
```
scoop install make
```
Cuối cùng khởi động lại `vscode`

- Build code và thực thi
```
make run
```
- Clear các file thực thi
```
make clear
```