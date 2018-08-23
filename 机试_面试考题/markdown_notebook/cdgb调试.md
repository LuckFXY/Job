启动命令 

g++ main.cpp -o main.out -lrt -g

cgdb main.out main.cpp

M-x   转换为intel格式的汇编
set disassembly-flavor att 转换为att格式的汇编

# emacs GDB

1. Alt+x (m+x)选中命令行，输入gdb
2. gdb -i=mi main.out

| 常用命令            | 含义                  | 默认快捷键 |
| ------------------- | --------------------- | ---------- |
| gdb-many-windows    | 切换单窗格/多窗格模式 |            |
| gdb-restore-windows | 恢复窗格布局          |            |
| gud-break           | 添加断点              |            |
| gud-remove          | 删除断点              |            |
| gud-go              | 运行或者继续          |            |
| gud-next            | 单步执行，无视函数    |            |
| gud-step            | 单步执行，进入函数    |            |
| gud-finish          | 跳出函数              |            |
| gud-until           | 运行到光标所在语句    |            |
| gud-cont            | 继续运行              |            |

这些 gud- 开头的命令都是 emacs gdb-mode 下通用调试器的操作命令，他们和 gdb 命令一一对应，可以用 m-x 输入这些命令，还可以直接用快捷键操作。

如果你想把某个窗口替换成反汇编或者寄存器的监控，那么可以用 m-x 输入：

```
gdb-display-disassembly-buffer
```

| Ctrl + E/K | 行末   |
| ---------- | ------ |
| CTRL + P   | 上一行 |
| CTRL + N   | 下一行 |

**调教 emacs gdb-mode**

打开 ~/.emacs （windows下是 ~/_emacs）文件，输入如下内容：

```
(global-set-key [M-left] 'windmove-left)
(global-set-key [M-right] 'windmove-right)
(global-set-key [M-up] 'windmove-up)
(global-set-key [M-down] 'windmove-down)

(global-set-key [f5] 'gud-run)
(global-set-key [S-f5] 'gud-cont)
(global-set-key [f6] 'gud-jump)
(global-set-key [S-f6] 'gud-print)
(global-set-key [f7] 'gud-step)
(global-set-key [f8] 'gud-next)
(global-set-key [S-f7] 'gud-stepi)
(global-set-key [S-f8] 'gud-nexti)
(global-set-key [f9] 'gud-break)
(global-set-key [S-f9] 'gud-remove)
(global-set-key [f10] 'gud-until)
(global-set-key [S-f10] 'gud-finish)

(global-set-key [f4] 'gud-up)
(global-set-key [S-f4] 'gud-down)

(setq gdb-many-windows t)
```

解释一下，最上面设定了 ALT + 方向键就可以在窗口中跳转，如果你终端 alt+方向不灵的话可以改成 C-left, C-right 等用 ctrl + 方向键移动窗口，后面设定了一些常用命令的快捷。

最后设置了默认打开 gdb-many-windows，最好增加下面一段，允许鼠标操作：

```
(require 'xt-mouse)
(xterm-mouse-mode)
(require 'mouse)
(xterm-mouse-mode t)
(defun track-mouse (e))

(setq mouse-wheel-follow-mouse 't)

(defvar alternating-scroll-down-next t)
(defvar alternating-scroll-up-next t)

(defun alternating-scroll-down-line ()
  (interactive "@")
    (when alternating-scroll-down-next
      (scroll-down-line))
    (setq alternating-scroll-down-next (not alternating-scroll-down-next)))

(defun alternating-scroll-up-line ()
  (interactive "@")
    (when alternating-scroll-up-next
      (scroll-up-line))
    (setq alternating-scroll-up-next (not alternating-scroll-up-next)))

(global-set-key (kbd "<mouse-4>") 'alternating-scroll-down-line)
(global-set-key (kbd "<mouse-5>") 'alternating-scroll-up-line)
```

这下 xterm 下你可以自用的用鼠标点击切换窗口，点击按钮，用滚轮上下查看源代码了：

[快捷键](./Emacs_快捷列表.md)