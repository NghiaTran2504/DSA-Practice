# EDITORIAL
## Core idea
**`Số cách thỏa = Tổng số cách xếp - Số cách xếp không thỏa`**

### **Số cách xếp không thỏa?**
![2x3 grid](./2x3.png)
![3x2 grid](./3x2.png)
<br>

*Cả 2 trường hợp trên đều có 2 trường hợp không thỏa*

### **Có bao nhiêu ô 2x3 và 3x2 trong grid n x n?**
<details>
<summary> Ans: </summary>

$$ 
2(n-1)(n-2)
$$

==> **Số ô không thỏa**: 

$$
4(n-1)(n-2)
$$

</details>

### Đáp án cuối cùng:
<details>
<summary> Nhấn để xem: </summary>

$$
 -4(n-1)(n-2)
$$

</details>

## Time & Space complexity
**Time:** O(1) <br>
**Space:** O(1)
 