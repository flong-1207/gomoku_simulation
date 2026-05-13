# Ý tưởng chính và Thiết lập AI

Thông thường, người chơi có ba xu hướng chính: Tấn công mạnh, phòng thủ chắc hoặc cân bằng cả hai. Team đặt ra bài toán: Nếu mỗi AI có “chỉ số tấn công” và “chỉ số phòng thủ” khác nhau thì AI nào sẽ chiến thắng nhiều hơn?

Giả sử, mỗi AI được khởi tạo với các hệ số:

  **AIPlayer player(PLAYER, HSatk, HSdef);**

Trong đó:

- HSAtk (Hệ số Tấn công): Đại diện cho phong cách chơi "khô máu", ưu tiên tạo chuỗi 3, 4 để kết thúc trận nhanh.

- HSDef (Hệ số Phòng thủ): Đại diện cho phong cách "xe buýt 2 tầng", ưu tiên chặn đứng mưu đồ của đối phương ngay từ khi mới có 2 quân liên tiếp.
