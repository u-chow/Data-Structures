# Data Structure

```
Program Homework 2
```
## • 題意說明

### 以C/C++語言寫一個程式來模擬一個文字編輯器，可新增英文大小寫字母，刪除

字母，可指定游標向右移或向左移，並可指定指令redo 及undo。

## • 功能要求

1. 顯示"Please enter an initial string consisting a/A-z/Z and space:" 並讀入input字
    串。
    輸入為一串由大小寫英文字母及空白所構成的字串。按"Enter"鍵則結束讀入，
    輸出輸入資料(游標位置在輸入字串最後)。
2. 提供以下功能指令：
    1) 新增字元(輸入a/A-z/Z and space)：從游標位置新增字元。
    2) 刪除字元(輸入 0 )：從游標位置向前刪除一個字元。
    3) 向左移動(輸入 1 )：游標位置向左移動一個字元，若游標位置不是在最後，
       則在該字元後加'|'表示。游標若移動到第一個字元，再執行向左移動，則
       不改變。
    4) 向左移動(輸入 2 )：游標位置向右移動一個字元，若游標位置不是在最後，
       則在該字元後加'|'表示。游標若移動到最後一個字元，再執行向右移動，
       則不改變。
    5) redo：重作被undo 的指令，指令順序跟被undo的順序相反。
    6) undo：回復前一指令(新增/刪除/向左/向右執行前的結果)。
    7) 按"Enter"鍵，印出指令執行後的字串結果。
    8) 可重覆以上功能指令，直到按"Esc"鍵則停止程式執行。

Example:
Suppose the initial text is "Hello, world!" and the cursor starts at the end of the text.
Insert 'X': "Hello world X" (cursor moves right)
Insert 'Y': "Hello world XY" (cursor moves right)
Delete: "Hello world X" (cursor stays in place)
Move left: "Hello world |X" (the '|' indicates the cursor position)
Undo: "Hello world X" (undoing the move left operation)
Redo: "Hello world |X" (redoing the move left operation)
Move right: "Hello world X" (cursor moves to the last)


- 程式內容需求
- 運用 **stack** 實作 **undo** 跟 **redo** 功能。
- 程式評分標準
    1. 正確性 ( 70 分)。
    2. 輸出入介面設計(考慮使用及操作便利性，結果顯示方式是否清楚明瞭)。
       ( 5 分)
    3. 程式撰寫模組化 (功能需採用對應模組撰寫)。(15分)
    4. 書面報告: 各主要procedure功能簡要說明，輸出入方式說明，檢附自行
       測試畫面結果。 (10分)
4. on time (- 10 分 each day late)
- Turned in

從moodle上傳 (必須附書面報告及source code), 若需要請配合助教在規定時間
內demo

## 明顯相互抄襲程式內容(e.g. 只有變數名稱不同者)、未繳交書面報告及

```
無法執行未配合助教 demo 者，以 0 分計算。
```
明顯相互抄襲程式內容(e.g. 只有變數名稱不同者)、未繳交書面報告及無法
執行未配合助教 **demo** 者，以 **0** 分計算。
