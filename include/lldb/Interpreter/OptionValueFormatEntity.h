//===-- OptionValueFormatEntity.h --------------------------------*- C++-*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef liblldb_OptionValueFormatEntity_h_
#define liblldb_OptionValueFormatEntity_h_

#include "lldb/Core/FormatEntity.h"
#include "lldb/Interpreter/OptionValue.h"

namespace lldb_private {

class OptionValueFormatEntity : public OptionValue {
public:
  OptionValueFormatEntity(const char *default_format);

  ~OptionValueFormatEntity() override {}

  // Virtual subclass pure virtual overrides

  OptionValue::Type GetType() const override { return eTypeFormatEntity; }

  void DumpValue(const ExecutionContext *exe_ctx, Stream &strm,
                 uint32_t dump_mask) override;

  Status
  SetValueFromString(llvm::StringRef value,
                     VarSetOperationType op = eVarSetOperationAssign) override;
  Status
  SetValueFromString(const char *,
                     VarSetOperationType = eVarSetOperationAssign) = delete;

  bool Clear() override;

  lldb::OptionValueSP DeepCopy() const override;

  void AutoComplete(CommandInterpreter &interpreter,
                    CompletionRequest &request) override;

  // Subclass specific functions

  FormatEntity::Entry &GetCurrentValue() { return m_current_entry; }

  const FormatEntity::Entry &GetCurrentValue() const { return m_current_entry; }

  void SetCurrentValue(const FormatEntity::Entry &value) {
    m_current_entry = value;
  }

  FormatEntity::Entry &GetDefaultValue() { return m_default_entry; }

  const FormatEntity::Entry &GetDefaultValue() const { return m_default_entry; }

protected:
  std::string m_current_format;
  std::string m_default_format;
  FormatEntity::Entry m_current_entry;
  FormatEntity::Entry m_default_entry;
};

} // namespace lldb_private

#endif // liblldb_OptionValueFormatEntity_h_
