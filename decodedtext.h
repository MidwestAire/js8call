// -*- Mode: C++ -*-
/*
 * Class to handle the formatted string as returned from the fortran decoder
 *
 * VK3ACF August 2013
 */


#ifndef DECODEDTEXT_H
#define DECODEDTEXT_H

#include "JS8.hpp"
#include <QString>
#include <QStringList>

class DecodedText
{
public:

  // Constructors

  explicit DecodedText(JS8::Event::Decoded const &);
  explicit DecodedText(QString const & frame,
                       int             bits,
                       int             submode);

  // Inline accessors

  int         bits()              const { return bits_;                  }
  QString     compoundCall()      const { return compound_;              }
  QStringList directedMessage()   const { return directed_;              }
  float       dt()                const { return dt_;                    }
  QString     extra()             const { return extra_;                 }
  QString     frame()             const { return frame_;                 }
  quint8      frameType()         const { return frameType_;             }
  int         frequencyOffset()   const { return frequencyOffset_;       }
  bool        isAlt()             const { return isAlt_;                 }
  bool        isCompound()        const { return !compound_.isEmpty();   }
  bool        isDirectedMessage() const { return directed_.length() > 2; }
  bool        isHeartbeat()       const { return isHeartbeat_;           }
  bool        isLowConfidence ()  const { return isLowConfidence_;       }
  QString     message()           const { return message_;               }
  int         snr()               const { return snr_;                   }
  int         submode()           const { return submode_;               }
  int         time()              const { return time_;                  }

  // Accessors

  QStringList messageWords() const;
  QString     string()       const;

private:

  // Unpacking strategies, attempted in order until one of them
  // works or all of them have failed.

  bool tryUnpackFastData (QString const &);
  bool tryUnpackData     (QString const &);
  bool tryUnpackHeartbeat(QString const &);
  bool tryUnpackCompound (QString const &);
  bool tryUnpackDirected (QString const &);

  static constexpr std::array unpackStrategies =
  {
    &DecodedText::tryUnpackFastData,
    &DecodedText::tryUnpackData,
    &DecodedText::tryUnpackHeartbeat,
    &DecodedText::tryUnpackCompound,
    &DecodedText::tryUnpackDirected
  };

  // Core constructor; delegated to by the public constructors.

  DecodedText(QString const & frame,
              int             bits,
              int             submode,
              bool            isLowConfidence,
              int             time,
              int             frequencyOffset,
              float           snr,
              float           dt);

  // Data members ** ORDER DEPENDENCY **

  quint8      frameType_;
  QString     frame_;
  bool        isAlt_;
  bool        isHeartbeat_;
  bool        isLowConfidence_;
  QString     compound_;
  QStringList directed_;
  QString     extra_;
  QString     message_;
  int         bits_;
  int         submode_;
  int         time_;
  int         frequencyOffset_;
  int         snr_;
  float       dt_;
};

#endif // DECODEDTEXT_H
