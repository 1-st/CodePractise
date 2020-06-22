struct Solution;

impl Solution {
    pub fn plus_one(digits: Vec<i32>) -> Vec<i32> {
        if digits.len() == 0 {
            return vec![];
        }
        let mut v = digits;
        let mut i = v.len() - 1;
        let mut expand = false;
        loop {
            if v[i] < 9 {
                v[i] = v[i] + 1;
                for ii in i + 1..v.len() {
                    v[ii] = 0;
                }
                break;
            } else if i == 0 {
                expand = true;
                break;
            }
            i = i - 1
        }
        return if !expand { v } else {
            let mut vv = Vec::new();
            vv.push(1);
            let mut l: i64 = v.len() as i64;
            while l > 0 {
                vv.push(0);
                l = l - 1
            }
            vv
        };
    }
}

fn main() {
    let v = vec![1,2,4,5];
    for i in Solution::plus_one(v) {
        print!("{} ", i)
    }
}
