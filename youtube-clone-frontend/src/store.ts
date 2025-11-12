import { create } from "zustand";


type UserLoggedIn = {
    value: {
        data: boolean;
        setUserLoggedIn: (loggedIn: boolean) => void;
    }
};

export const UserLoggedInStore = create<UserLoggedIn>((set) => ({
    value: {
        data: true,
        setUserLoggedIn: (loggedIn) => {
            set((state) => {
                state.value.data = loggedIn;
                return {value: {...state.value}};
            });
        },
    }
}));