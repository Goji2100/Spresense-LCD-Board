# Spresense-LCD-Board
## LCD board for Spresense
Spresenseの拡張ボードにスタックするLCDボードです
<br>

## 表示画面
<table>
<tr>
<td><img src="/DOC/CAP0320.png" width="400px"></td>
<td><img src="/DOC/CAP0480.png" width="400px"></td>
</tr>
<tr>
<td>表示画面（480 x 320）</td>
<td>表示画面（320 x 240）</td>
</tr>
</table>
<br>

## 組み立て完成写真
<img src="/DOC/IMG_4691.jpeg" width="800px"><br><br>

## LCDボードとSpresense拡張ボード
<img src="/DOC/IMG_4679.jpeg" width="800px"><br><br>

## LCDボード回路図
<img src="/DOC/Spresense_LCD_B.png" width="800px"><br><br>

## 使用するLCD
<img src="/DOC/HVGA_LCD.png" width="800px">

左）3.5 インチタッチスクリーン MHS TFT LCD モジュール[SPI 125MHz Support]<br>
右）GeeekPi 3.5インチ320 * 480モニタータッチパネル LCD[SPI 180MHz Support]　　
<br>
<br>
<br>

## その他のLCD
<table>
<tr><td><img src="/DOC/IMG_4708.jpeg" width="800px"></td></tr>
</table>
<br>

### Adafruit ILI9341
<table>
<tr>
<td><img src="/DOC/IMG_4712.jpeg" width="400px"></td>
<td><img src="/DOC/IMG_4714.jpeg" width="400px"></td>
</tr>
<tr>
<td>Adafruit ILI9341（表面） 320 x 240</td>
<td>Adafruit ILI9341（背面）</td>
</tr>
</table>

### Adafruit ILI9341 の組み込み
<table>
<tr>
<td><img src="/DOC/IMGS4800.png" width="800px"></td>
</tr>
<tr>
<td>フラットケーブルの折り曲げ加工、ILI9341の改造（TFT_CSをpin6に変更する）</td>
</tr>
</table>
<table>
<tr>
<td><img src="/DOC/IMGS4801.png" width="800px"></td>
</tr>
<tr>
<td>フラットケーブル取り付け、動作電圧の変更（Shieldは５V動作）</td>
</tr>
</table>
<table>
<tr>
<td><img src="/DOC/IMG_4732.jpeg" width="400px"></td>
</tr>
<tr>
<td>カメラは拡張ボードの背面に両面テープで貼り付け💦</td>
</tr>
</table>
<br>


### ILI9341(320 x 240)/ILI9488(480 x 320)
<table>
<tr>
<td><img src="/DOC/IMG_4748.jpeg" width="400"></td>
<td><img src="/DOC/IMG_4747.jpeg" width="400"></td>
</tr>
<tr>
<td>ILI9341（表面） 320 x 240</td>
<td>ILI9341（背面）</td>
</tr>
</table>
<br>

### ILI9341/ILI9488 の組み込み
<table>
<tr>
<td><img src="/DOC/IMG_4733.jpeg" width="400"></td>
<td><img src="/DOC/Shield2.png" width="400"></td>
</tr>
<tr>
<td>ILI9488（ILI9341とピン配置は同じ）</td>
<td>ILI9341/ILI9488と拡張ボードとの配線</td>
</tr>
</table>
<br>

<table>
<tr>
<td><img src="/DOC/IMG_4742.jpeg" width="400"></td>
<td><img src="/DOC/IMG_4739.jpeg" width="400"></td>
</tr>
<tr>
<td>実際の配線（ProtoType Shieldを経由します）</td>
<td>カメラフラットケーブルの折り曲げ加工</td>
</tr>
</table>
<br>


### ILI9486(480 x 320)
<table>
<tr>
<td><img src="/DOC/IMG_4718.jpeg" width="400"></td>
<td><img src="/DOC/IMG_4719.jpeg" width="400"></td>
</tr>
<tr>
<td>ILI9486（表面） 480 x 320</td>
<td>ILI9486（裏面）</td>
</tr>
</table>
<br>

## ILI9486の組み込み
### - ピンヘッダー５組
### - プルアップ抵抗（10kΩ）
### - 電源シュートジャンパーを半田付け
### - カメラをカメラマウンターに取り付け<br><br>
<img src="/DOC/IMG_4697.jpeg" width="600">
<br>
<br>

### カメラマウンター<br>
<img src="/DOC/Spresense_CAMERA_BASE7.jpg" width="600"></img>
#### [カメラマウンター] DOC/SPRESENSE CAMERA BASE7.stl <br>
#### [カメラマウンター　Tinkercad](https://www.tinkercad.com/things/2FAODkR43Zt-spresense-camera-base7)
<br><br>

## ビルド
1. フォルダ（camera_apitest）をArduinoスケッチフォルダーにコピー
2. ボードパッケージは "2.6.0" を使用します（3.xでは問題あり）
3. Memory:1536KBを選択
4. ライブラリーに "LovyanGFX(1.1.9)" と "XPT2046_Touchscreen" をインストール
5. Adafruit ILI9341のタッチパネルを使用する場合は "Adafruit_STMPE610" もインストール
6. ビルドしてアップロード


### define 文の変更（使用するLCDを選択）
<img src="/DOC/define.png" width="600"></img>
<br><br>

## 使用方法
- オリジナルはSpresenseのサンプルスケッチ->camera->camera_apitest.inoです<br>
  LovyanGFXでプレビュー表示するする処理を追加<br>
  タッチパネル読み取り処理を追加<br>
  オリジナルにあるSerialターミナルでのメニュー操作はそのままです<br>
  （写真の解像度、ISO感度などの設定、撮影画像のSDへの保存などができます）<br>
- タッチパネルによる写真撮影処理を追加
- 撮影した写真のサムネイル表示処理を追加（最新の5枚まで表示）
<br><br>
## ライセンス
[LovyanGFX](https://github.com/lovyan03/LovyanGFX/tree/master) [FreeBSD](https://github.com/lovyan03/LovyanGFX/blob/master/license.txt) lovyan03
<br>
[camera_apitest.ino]() [GNU]() Sony Semiconductor Solutions Corporation
<br>
