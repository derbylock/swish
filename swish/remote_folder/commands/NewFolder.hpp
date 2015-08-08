/* Copyright (C) 2011, 2012, 2013, 2015
   Alexander Lamaison <swish@lammy.co.uk>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by the
   Free Software Foundation, either version 3 of the License, or (at your
   option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SWISH_REMOTE_FOLDER_COMMANDS_NEW_FOLDER_HPP
#define SWISH_REMOTE_FOLDER_COMMANDS_NEW_FOLDER_HPP
#pragma once

#include "swish/provider/sftp_provider.hpp" // sftp_provider, ISftpConsumer
#include "swish/nse/Command.hpp" // Command

#include <washer/shell/pidl.hpp> // apidl_t
#include <washer/window/window.hpp>

#include <boost/optional/optional.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

namespace swish {
namespace remote_folder {
namespace commands {

typedef boost::function<
    boost::shared_ptr<swish::provider::sftp_provider>(
        comet::com_ptr<ISftpConsumer>, const std::string& task_name)> provider_factory;

typedef boost::function<comet::com_ptr<ISftpConsumer>()> consumer_factory;

class NewFolder : public swish::nse::Command
{
public:
    NewFolder(
        const boost::optional<washer::window::window<wchar_t>>& parent_window,
        const washer::shell::pidl::apidl_t& folder_pidl,
        const provider_factory& provider,
        const consumer_factory& consumer);
    
    virtual BOOST_SCOPED_ENUM(state) state(
        const comet::com_ptr<IDataObject>& data_object,
        bool ok_to_be_slow) const;

    void operator()(
        const comet::com_ptr<IDataObject>& data_object,
        const comet::com_ptr<IBindCtx>& bind_ctx) const;

    void set_site(comet::com_ptr<IUnknown> ole_site);

private:
    boost::optional<washer::window::window<wchar_t>> m_parent_window;
    washer::shell::pidl::apidl_t m_folder_pidl;
    provider_factory m_provider_factory;
    consumer_factory m_consumer_factory;
    comet::com_ptr<IUnknown> m_site;
};

}}} // namespace swish::remote_folder::commands

#endif
