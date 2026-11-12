#pragma once
#include <winsock2.h>
#include <windows.h>
#include <wx/wx.h>
#include <wx/msw/private.h>

namespace awx {

namespace detail {
inline HINSTANCE ThisModule()
{
    HMODULE module = nullptr;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       reinterpret_cast<LPCWSTR>(&ThisModule), &module);
    return module;
}
} // namespace detail

// DLL 内では wxIMPLEMENT_APP が使えないため、wx を手動で起動する。RegisterPlugin から呼ぶ。
//
// wxSetInstance で、wx の HINSTANCE を自分の DLL にしておくこと。
// 設定しないと NULL のままで、ウィンドウクラス名 (wxWindowClass など) が、
// 同じプロセス内の別の wx 製プラグインと衝突し、RegisterClass が失敗する。
inline bool StartWx()
{
    wxSetInstance(detail::ThisModule());
    wxApp::SetInstance(new wxApp());
    int argc = 0;
    if (!wxEntryStart(argc, static_cast<wchar_t**>(nullptr)))
        return false;
    wxTheApp->CallOnInit();
    return true;
}

// StartWx が成功していたときだけ呼ぶ。UninitializePlugin から、フレームを Destroy した後に呼ぶ。
inline void StopWx() { wxEntryCleanup(); }

} // namespace awx
