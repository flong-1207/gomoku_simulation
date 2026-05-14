# 🎮 Giới thiệu

Chúng ta sẽ đến với một "huyền thoại học đường": Cờ Caro.

Mô hình trên có sử dụng OOP (lập trình hướng đối tượng) kết hợp với thuật toán Minimax và cắt tỉa Alpha-Beta để chứng minh rằng:

**Trong cờ caro (Gomoku), chiến thắng không đến từ may mắn, mà là đến từ việc tối ưu hệ số tấn công/phòng thủ.**

Tổng quan luật chơi mô phỏng

- Bàn cờ: Hình vuông kích thước 10x10.  

- Quân cờ: Hai bên X và O.  

- Điều kiện thắng: Bên nào tạo được 5 quân liên tiếp (trên hàng dọc, 5 hàng ngang hoặc 5 hàng chéo) trước sẽ giành chiến thắng.

# 🧠 Ý tưởng chính và thiết lập AI

Thông thường, người chơi có ba xu hướng chính: Tấn công mạnh, phòng thủ chắc hoặc cân bằng cả hai. Chúng ta thử đặt ra bài toán rằng: 

**Nếu mỗi AI có “chỉ số tấn công” và “chỉ số phòng thủ” khác nhau thì AI nào sẽ chiến thắng nhiều hơn?**

Chính vì vậy, mô hình áp dụng các kỹ thuật tối ưu hóa để AI có thể xử lý trong thời gian thực:  

+ **Minimax**: Giả lập các nước đi của bản thân và đối thủ để tìm ra lựa chọn đem lại lợi ích tốt nhất.

+ **Alpha-Beta Pruning**: Cắt tỉa các nhánh không tối ưu (beta <= alpha) để giảm số lượng trạng thái cần duyệt trên bàn cờ 10x10, giúp AI chạy nhanh hơn.

+ **Tối ưu hóa _checkWin()_**: Chỉ kiểm tra xung quanh nước đi vừa đánh thay vì duyệt toàn bộ bàn cờ.

# 🛠 Áp dụng kiến thức OOP

Mô hình được cấu trúc theo tinh thần đóng gói (Encapsulation) với các thành phần chính:

_class Board_ (Quản lý toàn bộ logic và trạng thái của bàn cờ)

=> Dữ liệu: Bàn cờ được cấp phát động _char BanCo_. Các ô chứa giá trị _EMPTY_, _PLAYER_X_, hoặc _PLAYER_O_.
  
=> Trách nhiệm: Đặt quân, kiểm tra thắng thua, hoàn tác nước đi và tính điểm thế cờ. Toàn bộ logic bàn cờ nằm gọn trong class này.

=> Hàm _checkWin()_

+ Kiểm tra 4 hướng: ngang, dọc, chéo chính, chéo phụ.

+ Tối ưu: Chỉ kiểm tra quanh nước đi vừa đánh thay vì duyệt toàn bộ bàn cờ để giảm thời gian xử lý.

=> Hàm _countPatterns()_: Lượng giá các chuỗi 2, 3, 4 quân và số đầu hở để đưa ra nước đi mạnh nhất.

_class AIPlayer_ (Đại diện cho "bộ não" của AI với các chỉ số chiến thuật)

=> Hàm _player(PLAYER, HSatk, HSdef)_, trong đó:

+ Hệ số Tấn công (HSAtk): Đại diện cho phong cách chơi "khô máu", ưu tiên tạo chuỗi 3, 4 để kết thúc trận thắng 1 cách nhanh chóng.

+ Hệ số Phòng thủ (HSDef): Đại diện cho phong cách "xe buýt 2 tầng", ưu tiên chặn đứng mưu đồ của đối phương ngay từ khi mới có 2 quân liên tiếp.

=> Hàm _evaluate()_ (Đây là "bộ não" lượng giá thế trận)

+ Tính toán điểm số dựa trên các mẫu hình (patterns)

+ Công thức lượng giá: **Score = (atkScore * HSAtk) - (defScore * HSDef)**

# 💡 Cẩm Nang Chiến Thắng (Counter-Strategy)

Đối với quân X (Đi trước)   
+ Gặp đối thủ thủ mạnh: Sử dụng chiến thuật "Quá tải" (Overloading) tạo thế 4-3 hoặc 3-3.
+ Gặp đối thủ cân bằng: Tập trung chiếm lĩnh các ô trung tâm bàn cờ.
+ Gặp đối thủ công mạnh: Ép đối thủ vào thế phải đỡ bằng các nước "Chiếu" liên tục.

Đối với quân O (Đi sau)
+ Gặp đối thủ thủ mạnh: Xây dựng "pháo đài" vững chắc tại một góc.
+ Gặp đối thủ cân bằng: Di chuyển phá cấu trúc của X, mượn quân X làm vật cản cho chính họ.
+ Gặp đối thủ công mạnh: Đẩy $HSDef$ lên tối đa, chặn ngay từ 2 quân liên tiếp và chờ sơ hở để phản công.  

# Lời cuối cùng

Đằng sau mỗi nước đi là cả một ma trận điểm số đang nhảy múa. Chiến thắng cờ Caro bằng OOP không chỉ là việc viết code, mà còn giúp hiểu rõ sự cân bằng giữa Tấn công và Phòng thủ. Việc tách biệt trách nhiệm qua các Class và chuẩn bị kịch bản tương lai bằng Minimax sẽ là bài học quý giá cho cả lập trình lẫn cuộc sống.

P/S: Chúc các bạn "đè bẹp" được đối thủ bằng tư duy lập trình!
