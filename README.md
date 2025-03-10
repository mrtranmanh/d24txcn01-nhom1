# 🎯 Đồ án: Hệ thống Đăng nhập, Đăng ký Tài khoản & Quản lý Ví Điểm Thưởng

## 📌 **Giới thiệu**:  
Dự án phát triển một hệ thống đăng nhập và đăng ký tài khoản kết hợp với quản lý ví điểm thưởng, giúp người dùng dễ dàng tạo tài khoản, bảo mật thông tin cá nhân và theo dõi điểm thưởng một cách hiệu quả. Có người quản lý để đảm bảo hoạt động cũng như linh hoạt hỗ trợ. Điểm thưởng có thể quy đổi ra hàng hoá hoặc chuyển giữa các tài khoản. Hệ thống xay dung bang ngôn ngữ C++.

## 👥 **Thành viên nhóm & Phân công công việc chính**

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
- Ưu tiên viết function riêng hoặc file riêng
- Sử dụng cơ sử dũ liệu là file .txt

---

## Chức năng chi tiết

## Cách tải chương trình, dịch chương trình, các tập tin, các thư viện kèm theo
### Cách tải chương trình
- Truy cập vào nguồn tải chương trình (github).
- Tải tệp chương trình về máy tính của bạn (ví dụ: tệp nén `.zip`, `.tar.gz`, hoặc tệp thực thi `.exe`).
- Giải nén tệp nếu cần thiết và lưu trữ chương trình vào một thư mục dễ tìm trên máy tính.
- Mở thư mục chứa tệp đã tải về và tìm tệp thực thi chương trình (file main).
### Dịch chương trình
1. Ubuntu
- Tải phần mềm soạn code như Visual Code ...
- Cai them chuong trinh bien dich C++: sudo apt install build-essential
- Chạy lệnh biên dịch: g++ main.cpp register.cpp login.cpp utils.cpp -o main
+ Trên Windown: g++ main.cpp register.cpp login.cpp utils.cpp -o main.exe
2. Windows
- Tải phần mềm soạn code như Visual Code ...
- Cai them chuong trinh bien dich C++ như MinGW hoặc MSYS2:
+ Vào link https://code.visualstudio.com/docs/cpp/config-mingw
+ Tải phần mềm ở text "direct link to the installer" hoặc vào trực tiếp link https://github.com/msys2/msys2-installer/releases/download/2024-12-08/msys2-x86_64-20241208.exe
+ Chạy file tải về để cài đặt, nhớ chọn Run MSYS2 now khi hoàn thành
+ Chạy lệnh từ cửa sổ mở lên: pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
+ Trong thanh tìm kiếm của Windows, nhập Settings để mở Cài đặt Windows.
+ Tìm kiếm Edit environment variables for your account (Chỉnh sửa biến môi trường cho tài khoản của bạn).
+ Trong phần Biến của người dùng (User variables), chọn biến Path, sau đó nhấn Edit (Chỉnh sửa).
+ Nhấn New (Mới), rồi thêm thư mục cài đặt MinGW-w64 mà bạn đã ghi lại trong quá trình cài đặt vào danh sách.
+ Nếu bạn sử dụng cài đặt mặc định, đường dẫn sẽ là: C:\msys64\ucrt64\bin
+ Nhấn OK, sau đó nhấn OK một lần nữa trong cửa sổ Biến môi trường (Environment Variables) để cập nhật biến PATH.
+ Bạn cần đóng và mở lại bất kỳ cửa sổ dòng lệnh nào để biến PATH mới có hiệu lực.
- Chạy lệnh biên dịch trong Visual Code (Nhớ tắt đi rồi bật lại): g++ main.cpp register.cpp login.cpp utils.cpp -o main.exe

### Các tập tin, thu muc
- main (File thực thi)
- main.cpp (Gọi hàm)
- lib (Thư viện ngoai cho du an)
- users (Luu tru thong tin user)
- login.cpp (Xử lý đăng nhập)
- login.h (Khai báo hàm đăng nhập)
- register.cpp (Xử lý đăng ký)
- register.h (Khai báo hàm đăng ký)
- utils.cpp (Cài đặt hàm chung)
- utils.h (Hàm chung: hash mật khẩu, lưu & đọc dữ liệu ...)
### Các thư viện kèm theo
- lib/json.hpp: Thư viện JSON nlohmann/json
- regex: Thư viện regex để kiểm tra định dạng

## Cách chạy chương trình, thao tác thực hiện
Trên Ubuntu sử dụng lệnh ./main để chạy file main
Trên Windown click file main.exe để chạy

## Tài liệu đã tham khảo
https://json.nlohmann.me/
https://code.visualstudio.com/docs