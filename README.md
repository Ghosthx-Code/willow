# 🌿 Willow

### A Lightweight Open Source Programming Language

Willow is an experimental programming language featuring a custom **lexer**, **parser**, and **AST system**.
It is designed to explore language design, compilation, and low-level control with a clean and minimal syntax.

***`Version` 0.0.2***

---

## 🚀 Features

* Custom-built lexer, parser, and AST
* Simple and readable syntax
* Experimental function and type system
* Designed for future compiler/LLVM integration

---

## 📦 Installation

```bash
git clone https://github.com/Ghosthx-Code/willow.git
gcc willow/build/oak.c -o oak
sudo mv /usr/local/bin/
cd willow
make
```

---

## ✨ Example

```c
@define <willow>;

func main() ? <- i32 {
    printfl:("Hello, world")?;
}
```

## 🧠 Language Notes

* `?` → marks execution flow / control points
* `<-` → defines return types
* `:` → used for function-style calls and declarations
* `;` → terminates statements

---

## 🛠 Roadmap

* [ ] If lexer, parser, ast does not work fix it
* [ ] Make lexer, parser, ast faster
* [ ] Full expression support (`+ - * /`)
* [ ] Function arguments + returns
* [ ] Better type system
* [ ] LLVM backend / compiler
* [ ] Standard library

---

## 🚧 Status

⚠️ Willow is in **early development**.
Expect breaking changes and incomplete features.

---

## 🤝 Contributing

Contributions are welcome.

* Open an issue for bugs or ideas
* Submit a pull request for improvements

## MTL

* Mtl license

---
