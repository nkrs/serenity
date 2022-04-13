/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "DNSAnswer.h"
#include <AK/Stream.h>
#include <time.h>

namespace DNS {

DNSAnswer::DNSAnswer(DNSName const& name, DNSRecordType type, DNSRecordClass class_code, u32 ttl, String const& record_data, bool mdns_cache_flush)
    : m_name(name)
    , m_type(type)
    , m_class_code(class_code)
    , m_ttl(ttl)
    , m_record_data(record_data)
    , m_mdns_cache_flush(mdns_cache_flush)
{
    time(&m_received_time);
}

bool DNSAnswer::has_expired() const
{
    return time(nullptr) >= m_received_time + m_ttl;
}

}

ErrorOr<void> AK::Formatter<DNS::DNSRecordType>::format(AK::FormatBuilder& builder, DNS::DNSRecordType value)
{
    switch (value) {
    case DNS::DNSRecordType::A:
        return builder.put_string("A");
    case DNS::DNSRecordType::NS:
        return builder.put_string("NS");
    case DNS::DNSRecordType::CNAME:
        return builder.put_string("CNAME");
    case DNS::DNSRecordType::SOA:
        return builder.put_string("SOA");
    case DNS::DNSRecordType::PTR:
        return builder.put_string("PTR");
    case DNS::DNSRecordType::MX:
        return builder.put_string("MX");
    case DNS::DNSRecordType::TXT:
        return builder.put_string("TXT");
    case DNS::DNSRecordType::AAAA:
        return builder.put_string("AAAA");
    case DNS::DNSRecordType::SRV:
        return builder.put_string("SRV");
    }

    TRY(builder.put_string("DNS record type "));
    TRY(builder.put_u64((u16)value));
    return {};
}

ErrorOr<void> AK::Formatter<DNS::DNSRecordClass>::format(AK::FormatBuilder& builder, DNS::DNSRecordClass value)
{
    switch (value) {
    case DNS::DNSRecordClass::IN:
        return builder.put_string("IN");
    }

    TRY(builder.put_string("DNS record class "));
    TRY(builder.put_u64((u16)value));
    return {};
}