# 🌿 Willow

### An Open Source Programming Language

Willow is a lightweight experimental programming language with a simple syntax and custom parser.

---

## 📦 Installation

```bash
git clone https://github.com/yourusername/willow.git
cd willow
make
```

---

## ✨ Example

```c
@define <willow>;

func main() ? <- i32 {
    printfl:( "Hello, world" )?;
}
```

---

## 📚 Syntax Overview

### 🔹 Import

```c
@define <willow>;
```

### 🔹 Function

```c
func main() ? <- i32 {

}
```

### 🔹 Print

```c
printfl:( "Hello" )?;
```

### 🔹 Input

```c
inputfl:( x )?;
```

### 🔹 Vars
```c
<data-type>: <name> = <value>?;
-- like
i32: x = 10?;
```

### 🔹 Making Functions
```c
func <name>(<vars>) ? <- <data-type> {
    printfl:("%v", <vars>)?;
}
```

### 🔹 if, else if, else
```C
if (<name> == <value>) ? <- <output-type> {
    printfl:("Hello %v!", <name>)?;
}else ? <- <output-type> {
    printfl:("Hello %v", <name>?;
}
```

### 🔹 Loops
```C
while (*true) ? <- <return-type> {
    printfl:("Hello %v!", <name>)?;
}

-- for loops
for (i32: x = 0; x < 10; x++) ? <- i32 ? <- i8* {
    printfl:("Number: %v", x)?;
}
```

---

## 🧠 Notes

* `?` is used to mark execution flow points
* `<-` defines return types
* `:` is used for function-style calls
* `;` terminates statements

---

## 🚧 Status

⚠️ Willow is in early development. Features may change.

---

## 🤝 Contributing

Pull requests are welcome. For major changes, open an issue first.

---
