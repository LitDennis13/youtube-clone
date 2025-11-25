import { create } from "zustand";

import { PageOptions } from "./types";


type UserLoggedIn = {
    value: {
        data: boolean;
        setUserLoggedIn: (loggedIn: boolean) => void;
    }
};

export const UserLoggedInStore = create<UserLoggedIn>((set) => ({
    value: {
        data: false,
        setUserLoggedIn: (loggedIn: boolean) => {
            set((state) => {
                state.value.data = loggedIn;
                return {value: {...state.value}};
            });
        },
    }
}));

type SelectedPage = {
    value: {
        page: PageOptions,
        setSelectedPage: (newPage: PageOptions) => void,
    }
}

export const SelectedPageStore = create<SelectedPage>((set) => ({
    value: {
        page: 0,
        setSelectedPage: (newPage: PageOptions) => {
            set((state) => {
                state.value.page = newPage;
                return ({value: {...state.value}});
            })
        }
    }
}));


type DisplayExtendedMenu = {
    value: {
        data: boolean,
        setDisplayExtendedMenu: (displayExtendedMenu: boolean) => void,
    }
}

export const DisplayExtendedMenuStore = create<DisplayExtendedMenu>((set) => ({
    value : {
        data: false,
        setDisplayExtendedMenu: (displayExtendedMenu: boolean) => {
            set((state) => {
                state.value.data = displayExtendedMenu;
                return {value: {...state.value}};
            });
        }
    }
}));