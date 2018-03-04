/// <copyright file="dumpmmpld.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#include "stdafx.h"

#define MAJOR_VERSION (1)
#define MINOR_VERSION (0)


/// <summary>
/// Find (case-insensitively) the given switch in the given range.
/// </summary>
template<class I, class T> I FindSwitch(I begin, I end, const T *name) {
    std::basic_string<T> n(name);
    return std::find_if(begin, end, [&n](const std::basic_string<T>& s) {
        return ((n.length() == s.length())
            && std::equal(n.cbegin(), n.cend(), s.cbegin(),
            [](T l, T r) { return (std::tolower(l) == std::tolower(r)); }));
    });
}

/// <summary>
/// Find (case-insensitively) the given switch and return its argument.
/// </summary>
template<class I, class T> I FindArgument(I begin, I end, const T *name) {
    auto retval = ::FindSwitch(begin, end, name);
    return (retval != end) ? ++retval : retval;
}


/// <summary>
/// Entry point of dumpmmpld.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int _tmain(const int argc, const _TCHAR **argv) {
    const std::vector<std::basic_string<_TCHAR>> CMD_LINE(argv, argv + argc);

    {
        auto it = ::FindSwitch(CMD_LINE.begin(), CMD_LINE.end(), _T("/nologo"));
        if (it == CMD_LINE.end()) {
            std::tcout << _T("dumpmmpld ") << MAJOR_VERSION << _T(".")
                << MINOR_VERSION << std::endl;
            std::tcout << _T("Copyright (C) 2018 Visualisierungsinstitut der ")
                _T("Universität Stuttgart.") << std::endl;
            std::tcout << _T("Alle Rechte vorbehalten.") << std::endl;
            std::tcout << std::endl;
        }
    }

    try {
        std::basic_string<_TCHAR> path;

        {
            auto it = ::FindArgument(CMD_LINE.begin(), CMD_LINE.end(),
                _T("/path"));
            if (it != CMD_LINE.end()) {
                path = *it;
            } else {
                throw std::runtime_error("The mandatory command line argument "
                    "/path is missing.");
            }
        }

        std::tcout << _T("Path           : ")
            << path << std::endl;
        mmpld::file<HANDLE, _TCHAR> file(path.c_str());

        /* Dump information from MMPLD file header. */
        {
            unsigned int major, minor;
            file.version(major, minor);
            std::tcout << _T("Version        : ") 
                << major << _T(".") << minor
                << std::endl;
        }

        std::tcout << _T("Frames         : ")
            << file.file_header().frames
            << std::endl;

        std::tcout << _T("Bounding Box   : (")
            << file.file_header().bounding_box[0] << _T(", ")
            << file.file_header().bounding_box[1] << _T(", ")
            << file.file_header().bounding_box[2] << _T(") - (")
            << file.file_header().bounding_box[3] << _T(", ")
            << file.file_header().bounding_box[4] << _T(", ")
            << file.file_header().bounding_box[5] << _T(")")
            << std::endl;

        std::tcout << _T("Clipping Box   : (")
            << file.file_header().clipping_box[0] << _T(", ")
            << file.file_header().clipping_box[1] << _T(", ")
            << file.file_header().clipping_box[2] << _T(") - (")
            << file.file_header().clipping_box[3] << _T(", ")
            << file.file_header().clipping_box[4] << _T(", ")
            << file.file_header().clipping_box[5] << _T(")")
            << std::endl;

        /* Dump all frames. */
        for (size_t f = 0; f < file.frames(); ++f) {
            file.open_frame(f);

            std::tcout << std::endl;
            std::tcout << _T("Frame          : ")
                << file.frame()
                << std::endl;

            std::tcout << _T("Particle lists : ")
                << file.frame_header().lists
                << std::endl;

            std::tcout << _T("timestamp      : ")
                << file.frame_header().timestamp
                << std::endl;
        }

        return 0;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return -1;
    }

}

