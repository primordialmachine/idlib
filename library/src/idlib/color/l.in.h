// Copyright Michael Heilmann 2016, 2017, 2018.
//
// This file is part of Idlib.
//
// Idlib is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Idlib is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Idlib. If not, see <http://www.gnu.org/licenses/>.

    /// @brief Get the value of the luminance component.
    /// @return the value of the luminance component
    const component_l& get_luminance() const noexcept
    { return l; }
#if defined(ID_COLOR_SHORT_GETTERS) && 1 == ID_COLOR_SHORT_GETTERS
    /// @brief Get the value of the luminance component.
    /// @return the value of the luminance component
    const component_l& get_l() const noexcept
    { return l; }
#endif
