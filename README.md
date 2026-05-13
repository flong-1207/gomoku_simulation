# Giới thiệu

Chúng ta sẽ đến với một "huyền thoại học đường": Cờ Caro.

Mô hình trên có sử dụng OOP (lập trình hướng đối tượng) kết hợp với thuật toán Minimax để chứng minh rằng:

**Trong cờ caro (Gomoku), kẻ chiến thắng không phải kẻ may mắn, mà là kẻ có hệ số tấn công/phòng thủ tối ưu nhất.**

Luật chơi mô phỏng

- Bàn cờ: Hình vuông kích thước 10x10.  

- Quân cờ: Hai bên X và O.  

- Điều kiện thắng: Bên nào tạo được 5 hàng dọc, 5 hàng ngang hoặc 5 hàng chéo trước sẽ giành chiến thắng.

# Ý tưởng chính và Thiết lập AI

Thông thường, người chơi có ba xu hướng chính: Tấn công mạnh, phòng thủ chắc hoặc cân bằng cả hai. Chúng ta thử đặt ra bài toán rằng: 

**Nếu mỗi AI có “chỉ số tấn công” và “chỉ số phòng thủ” khác nhau thì AI nào sẽ chiến thắng nhiều hơn?**

Giả sử, mỗi AI được khởi tạo với các hệ số:

_AIPlayer player(PLAYER, HSatk, HSdef);_

Trong đó:

- _HSAtk_ (Hệ số Tấn công): Đại diện cho phong cách chơi "khô máu", ưu tiên tạo chuỗi 3, 4 để kết thúc trận nhanh.

- _HSDef_ (Hệ số Phòng thủ): Đại diện cho phong cách "xe buýt 2 tầng", ưu tiên chặn đứng mưu đồ của đối phương ngay từ khi mới có 2 quân liên tiếp.

# Áp dụng kiến thức OOP

Mô hình được cấu trúc theo tinh thần đóng gói (Encapsulation) với các thành phần chính:

_class Board_ (Quản lý bàn cờ)

+ Dữ liệu: Bàn cờ được cấp phát động _char BanCo_. Các ô chứa giá trị _EMPTY_, _PLAYER_X_, hoặc _PLAYER_O_.  
+ Trách nhiệm: Đặt quân, kiểm tra thắng thua, hoàn tác nước đi và tính điểm thế cờ. Toàn bộ logic bàn cờ nằm gọn trong class này. 

Hàm _checkWin()_

+ Kiểm tra 4 hướng: ngang, dọc, chéo chính, chéo phụ.

+ Tối ưu: Chỉ kiểm tra quanh nước đi vừa đánh thay vì duyệt toàn bộ bàn cờ để giảm thời gian xử lý.

Hàm _countPatterns()_ & _evaluate()_ (Đây là "bộ não" lượng giá thế trận)

+ Lượng giá các chuỗi 2, 3, 4 quân và số đầu hở.

+ Công thức tổng quát: **Score = (atkScore * HSAtk) - (defScore * HSDef)**

# Lời cuối cùng

Chiến thắng cờ Caro bằng OOP không chỉ là việc viết code, mà là hiểu rõ sự cân bằng giữa Tấn công và Phòng thủ. Việc tách biệt trách nhiệm qua các Class và chuẩn bị kịch bản tương lai bằng Minimax là bài học quý giá cho cả lập trình lẫn cuộc sống.

P/S: Chúc các bạn "đè bẹp" được đối thủ bằng tư duy lập trình!
