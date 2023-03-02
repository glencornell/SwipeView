#pragma once

// Custom format parser for the XDG Desktop Entry specification.

// Note that this is not compliant with the specification in the
// following ways:
//
// * It is not idempotent: what it writes is not what it reads
// * It does not support localized strings

#include <QSettings>

QSettings::Format XdgDesktopSettingsFormat(bool makeDefault = true);
