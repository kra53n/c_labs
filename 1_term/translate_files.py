import os
import re
import shutil

src_path = r"D:\university\programming\msvs_files"
dst_path = r"C:\Users\Юзер\Desktop\projects\c_labs\1_term"

def get_lab_num(s):
    num = ""
    flag = False
    for i in s:
        if i.isdigit():
            flag = True
        if flag:
            if i.isdigit():
                num += i
            else:
                return num
    return num if len(num) else None


for root, dirs, files in os.walk(src_path):
    if ".cpp" not in "".join(files):
        continue
    if r"D:\university\programming\msvs_files\lab" not in root:
        continue
    
    lab_num = get_lab_num(root)
    filename = [i for i in files if ".cpp" in i][0]
    src = os.path.join(root, filename)
    dst = os.path.join(dst_path, lab_num)
    
    shutil.copy(src, dst)
    print(f":: {filename} was copied to {dst}")
