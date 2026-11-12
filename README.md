# aviutl2-wx-utils

Claude により作成された、AviUtl2 のプラグインから wxWidgets を使うための共通ヘルパーです。名前空間は `awx`となります。

| ヘッダ                              | 内容                                                                  |
| ----------------------------------- | --------------------------------------------------------------------- |
| `dpi_patch.hpp`                     | 登録した wx フレームの High DPI 対策 (`AviUtl2DpiPatch`)              |
| `modal_guard.hpp`                   | wxMessageBox / ShowModal を AviUtl2 上でモーダルにする (`ModalGuard`) |
| `message_box.hpp`                   | ModalGuard + テーマ色付きの `ShowMessageBox`                          |
| `get_colour.hpp`, `apply_theme.hpp` | style.conf のテーマ色の取得と適用                                     |

## 前提

利用側の `include/` に、次の3つを submodule として並べる必要があります。

```
include/
├─ aviutl2_sdk_mirror/   (https://github.com/aviutl2/aviutl2_sdk_mirror)
├─ wxCustomControls/     (https://github.com/nullruptr/wxCustomControls)
└─ aviutl2-wx-utils/     (このリポジトリ)
```

## 使い方

```cmake
find_package(wxWidgets CONFIG REQUIRED)
add_subdirectory(${ROOT}/include/aviutl2-wx-utils ${CMAKE_BINARY_DIR}/aviutl2-wx-utils)
target_link_libraries(plugin PRIVATE aviutl2_wx_utils::aviutl2_wx_utils)
```

- SDK と wxCustomControls の include パスは、このライブラリが公開する (利用側で設定不要)。
- `InitializeConfig` で `awx::theme::SetConfig(handle)` を呼ぶ。
- `RegisterPlugin` で `awx::SetEditHandle(host->create_edit_handle())` を呼ぶ。
