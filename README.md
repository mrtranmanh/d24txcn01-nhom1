# 🎯 Đồ án: Hệ thống Đăng nhập, Đăng ký Tài khoản & Quản lý Ví Điểm Thưởng

## 📌 Giới thiệu
Dự án phát triển một hệ thống đăng nhập và đăng ký tài khoản kết hợp với quản lý ví điểm thưởng, giúp người dùng dễ dàng tạo tài khoản, bảo mật thông tin cá nhân và theo dõi điểm thưởng một cách hiệu quả. Có người quản lý để đảm bảo hoạt động cũng như linh hoạt hỗ trợ. Điểm thưởng có thể quy đổi ra hàng hoá hoặc chuyển giữa các tài khoản. Hệ thống xây dựng bằng ngôn ngữ C++.

## 👥 Thành viên nhóm & Phân công công việc chính

| Họ và Tên       | Lớp             | Mã SV        | Công việc phụ trách                          |
|----------------|----------------|-------------|---------------------------------------------|
| **Trần Duy Mạnh** | D24TXCN01-B    | B24DTCN004  | Setup ban đầu, phân chia công việc, Đồ án Phần A |
| **Tạ Thu Hà**   | D24TXCN01-B    | B24DTCN003  | Tester, tổng kết báo cáo, Đồ án Phần B     |
| **Trần Anh Thái** | D23TXCN02-K    | K23DTCN200  | Đồ án Phần C                               |

### Yêu cầu thêm:
- Commit ghi theo format sau: <Loại commit> (feature/update/fix): <Mô tả ngắn> (<Tên>). Ví dụ: fix: hien thi diem thuong (Manh)
- Khi xảy ra conflict người upload sau có nhiệm vụ fix
- Sau khi xong nhiệm vụ có trách nhiệm bàn giao cũng hỗ trợ thành viên khác với những task chưa hoàn thành
- Source khi viết có thêm chú thích
- Ưu tiên mỗi chức năng đưa ra function riêng hoặc file riêng
- Sử dụng cơ sở dữ liệu là file .txt, .json

## 🛠️ Chức năng chi tiết

### A1. Tạo mới tài khoản khi đăng ký
- Người dùng có thể nhập dữ liệu để tạo tài khoản
- Cấu trúc thông tin người dùng:
    - user_id: hế thống tự động tạo
    - Username: Trường tên đăng nhập, bắt buộc phải nhập (4-32 ký tự)
    - Password: Mật khẩu đăng nhập (6-64 ký tự)
    - FullName: Danh tính người sở hữu tài khoản (Chỉ gồm chữ cái và dấu cách, từ 2-50 ký tự)
    - Gender: Giới tính người sở hữu tài khoản (Cho phép 2 lựa chọn Nam/Nữ)
    - Address: Địa chỉ người sở hữu tài khoản (Tối đa 255 ký tự)
    - Phone: Điện thoại người sở hữu tài khoản (Chỉ cho phép điền số)
    - Email: Email người sở hữu tài khoản (kiểm tra theo định dạng example@abc.com)
    - Birthday: Ngày tháng năm sinh người sở hữu tài khoản (định dạng dd//mm//yyyy)
    - Points: Điểm thưởng (Mặc định ban đầu là 0)
    - Role: loại tài khoản (Người dùng / quản lý), mặc định ban đầu là Nguoi_Dung

### A2. Lưu trữ dữ liệu
- Lưu lại dữ liệu tài khoản người dùng vào tập tin txt hoặc json
- Sử  dụng cấu trúc mỗi tài khoản là một thư mục riêng
- Mật khẩu được mã hóa
- Backup dữ liệu:
    - Tự động: mỗi 7 ngày khi người quản lý đăng nhập
    - Thủ công: chức năng trong bảng quản trị của người quản lý

### A3. Quản lý đăng nhập
- Mật khẩu tự động tạo khi không nhập
- Người dùng có thể tự thay đổi mật khẩu
- Người dùng nhận được yêu cầu thay đổi mật khẩu trong lần đăng nhập đầu tiên nếu là mật khẩu tự sinh
- OTP - One Time Password 🔴
- Cho phép đăng nhập bằng tài khoản đã có và thực hiện chức năng tương ứng

### B1. Tài khoản người dùng và chức năng
- Người dùng thông thường được phép truy xuất và sửa thông tin cá nhân của mình 🔴
- Gửi thông báo khi người dùng sửa thông tin 🔴
- Xác nhận OTP của người dùng rồi mới thay đổi thông tin thành công 🔴

### B2. Tài khoản người quản lý và chức năng
- Theo dõi danh sách nhóm 🔴
- Tạo thêm tài khoản mới 🔴
- Điều chỉnh thông tin của tài khoản khi có yêu cầu từ chủ tài khoản (làm hộ). Khi điều chỉnh xong, hệ thống gửi một mã OTP đến chủ tài khoản cùng thông báo các nội dung sẽ thay đổi để chủ tài khoản xác nhận thao tác cập nhật. Nếu mã OTP do chủ tài khoản nhập vào hợp lệ, hệ thống tiến hành cập nhật thông tin của người dùng. 🔴

### C. Quản lý hoạt động ví
- Mỗi người dùng có một bộ dữ liệu về số điểm (ví - wallet) 🔴
- Lưu trữ dữ liệu các giao dịch trao đổi, chuyển điểm từ một ví sang một ví khác. 🔴
- Một ví có mã số định danh duy nhất phân biệt với tất cả các ví còn lại. 🔴
- Ví tổng: nguồn duy nhất sinh ra tổng số điểm sẽ lưu chuyển trong toàn bộ hệ thống. 🔴
- Giao dịch chuyển điểm giữa các ví 🔴
- Sử dụng OTP để xác nhận thực hiện giao dịch chuyển điểm giữa các ví 🔴
- Hệ thống ghi nhận lại giao dịch này trong lịch sử giao dịch (transaction log) 🔴
- Cho phép người dùng theo dõi số dư, lịch sử giao dịch (và trạng thái thực hiện giao dịch) 🔴

### D. Chức năng mở rộng
- Thu gọn câu lệnh biên dịch 🔴
- Mật khẩu ẩn khi gõ 🔴
- Test trên macOS 🔴

## 📥 Cách tải chương trình, dịch chương trình, các tập tin, các thư viện kèm theo

### 1. Cách tải chương trình
- Truy cập vào nguồn tải chương trình (github).
- Tải tệp chương trình về máy tính của bạn (ví dụ: tệp nén `.zip`, `.tar.gz`, hoặc tệp thực thi `.exe`).
- Giải nén tệp nếu cần thiết và lưu trữ chương trình vào một thư mục dễ tìm trên máy tính.
- Mở thư mục chứa tệp đã tải về và tìm tệp thực thi chương trình (file main).
### 2. Dịch chương trình
#### 2.1. Linux
- Tải phần mềm soạn code như Visual Code ...
- Cai them chuong trinh bien dich C++: sudo apt install build-essential
- Chạy lệnh biên dịch:
```bash
g++ main.cpp register.cpp login.cpp utils.cpp dashboard.cpp backup.cpp changepassword.cpp -o main
```
#### 2.2. Windows
- Tải phần mềm soạn code như Visual Code ...
- Cai them chuong trinh bien dich C++ như MinGW hoặc MSYS2, ví dụ như sau:
    + Vào link https://code.visualstudio.com/docs/cpp/config-mingw
    + Tải phần mềm ở text "direct link to the installer" hoặc vào trực tiếp link https://github.com/msys2/msys2-installer/releases/download/2024-12-08/msys2-x86_64-20241208.exe
    + Chạy file tải về để cài đặt, nhớ chọn Run MSYS2 now khi hoàn thành
    + Chạy lệnh từ cửa sổ mở lên:
    ```bash
    pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
    ```
    + Trong thanh tìm kiếm của Windows, nhập Settings để mở Cài đặt Windows.
    + Tìm kiếm Edit environment variables for your account (Chỉnh sửa biến môi trường cho tài khoản của bạn).
    + Trong phần Biến của người dùng (User variables), chọn biến Path, sau đó nhấn Edit (Chỉnh sửa).
    + Nhấn New (Mới), rồi thêm thư mục cài đặt MinGW-w64 mà bạn đã ghi lại trong quá trình cài đặt vào danh sách.
    + Nếu bạn sử dụng cài đặt mặc định, đường dẫn sẽ là: C:\msys64\ucrt64\bin
    + Nhấn OK, sau đó nhấn OK một lần nữa trong cửa sổ Biến môi trường (Environment Variables) để cập nhật biến PATH.
    + Bạn cần đóng và mở lại bất kỳ cửa sổ dòng lệnh nào để biến PATH mới có hiệu lực.
- Chạy lệnh biên dịch trong Visual Code (Nhớ tắt đi rồi bật lại):
```bash
g++ main.cpp register.cpp login.cpp utils.cpp dashboard.cpp backup.cpp changepassword.cpp -o main.exe
```
- Video thao tác chi tiết: https://www.youtube.com/watch?v=oC69vlWofJQ

### 3. Các tập tin, thư mục
- backup (Thư mục lưu trữ các bản backup)
- lib (Thư mục thư viện ngoài cho dự án)
- users (Thư mục lưu trữ thông tin user)
- backup.h, backup.cpp (File Khai báo và Xử lý chức năng Backup)
- backup/last_backup.txt (File lưu trữ thời gian backup cuối)
- changepassword.h, changepassword.cpp (File Khai báo và Xử lý chức năng Thay đổi password)
- dashboard.h, dashboard.cpp (File Khai báo và Xử lý trang quan tri)
- login.h, login.cpp (File Khai báo và Xử lý đăng nhập)
- main, main.exe (File thực thi)
- main.cpp (File điều khiển chính)
- register.h register.cpp (File Khai báo và Xử lý đăng ký)
- utils.h, utils.cpp (File Khai báo và Xử lý cài đặt hàm chung như hash mật khẩu, lưu & đọc dữ liệu ...)

### 4. Các thư viện kèm theo
- filesystem: Quản lý tệp và thư mục (Thư viện chuẩn của C++17)
- fstream: Thư viện đọc/ghi file (Thư viện chuẩn của C++)
- iostream: Thư viện dùng để nhập xuất dữ liệu (Thư viện chuẩn của C++)
- lib/json.hpp: Thư viện JSON nlohmann/json (Đã tích hợp sẵn trong dự án)
- regex: Thư viện regex để kiểm tra định dạng (Thư viện chuẩn của C++11)

## ⚙️ Cách chạy chương trình, thao tác thực hiện
Trên Linux sử dụng lệnh ./main để chạy file main  
Trên Windown click đúp file main.exe để chạy

## 📚 Tài liệu đã tham khảo
[1] JSON https://json.nlohmann.me/  
[2] Visualstudio C++ https://code.visualstudio.com/docs/cpp/config-linux