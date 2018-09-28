# 1 删除大文件

https://juejin.im/entry/5812a6512e958a005489686a

## 1 查看那些实例提交文件占用内存过大

```git
git rev-list --objects --all | grep "$(git verify-pack -v .git/objects/pack/*.idx | sort -k 3 -n | tail -5 | awk '{print$1}')"
```

- rev-list命令用来列出Git仓库中的提交，我们用它来列出所有提交中涉及的文件名及其ID。 该命令可以指定只显示某个引用（或分支）的上下游的提交。
- --objects：列出该提交涉及的所有文件ID。
- --all：所有分支的提交，相当于指定了位于/refs下的所有引用。
- verify-pack命令用于显示已打包的内容。

## 2. 重写 commit 删除大文件

使用以下命令，删除历史提交过的大文件：

```
git filter-branch --force --index-filter 'git rm -rf --cached --ignore-unmatch big-file.jar' --prune-empty --tag-name-filter cat -- --all
```

- 上面脚本中的big-file.jar请换成你第一步查出的大文件名，或者这里直接写一个目录。
- filter-branch命令可以用来重写Git仓库中的提交
- --index-filter参数用来指定一条Bash命令，然后Git会检出（checkout）所有的提交， 执行该命令，然后重新提交。
- --all参数表示我们需要重写所有分支（或引用）。

## 3 强制推送修改后的repo

```
git push origin master --force
```

## 4 清理和回收空间

- rm -rf .git/refs/original/ 
- git reflog expire --expire=now --all 
- git gc --prune=now 

