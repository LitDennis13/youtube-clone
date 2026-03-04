import { create } from "zustand";

import { UserData, PageOptions } from "./types";


const placeholderUseData: UserData = {
    userStatus: -1,
    userID: -1,
    username: "",
    userLoggedIn: false,
};

type UserDataStoreType = {
    value: UserData;
    setUserData: (newUserData: UserData) => void;

};

export const UserDataStore = create<UserDataStoreType>((set) => ({
    value: placeholderUseData,
    setUserData: (newUserData: UserData) => {
        set((state) => {
            state.value = newUserData;
            return ({value: {...state.value}});
        })
    }
}));

type SelectedPage = {
    value: {
        page: PageOptions;
        setSelectedPage: (newPage: PageOptions) => void;
    };
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
        data: boolean;
        setDisplayExtendedMenu: (displayExtendedMenu: boolean) => void;
    };
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